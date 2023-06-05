#ifndef GAME
#define GAME

#include <stdint.h>
#include "Arduino.h"
#include "sprites.h"

enum game_fase{
  NEW_PIECE, MOVEMENT, CHECKOUT, FALL
};

typedef struct {
  sprite form;
  int8_t pos_x; // posicion % 8
  uint8_t pos_y; // posicion % map_size
  uint8_t rot; // rotacion % 4
  uint8_t num; // numero de pieza [0-6]
} Pieza;

typedef struct {
  unsigned long inv_fps;
  game_fase state;
  uint8_t next;
  Pieza pieza;
  Pieza hitbox;
  uint8_t map_size;
} Game;

Game game;

// =======================================================================

void game_setup(uint8_t FPS, uint8_t map_size = 24){
  game.inv_fps = 1000 / FPS;
  game.state = NEW_PIECE;
  game.map_size = map_size;
  game.next = 7;
}

void game_change_FPS(uint8_t FPS){
  game.inv_fps = 1000 / FPS;
}

// ======================================================================

bool game_check_x_mov(sprite box, bool right){
  bool retorn = true;

  if (right) { // derecha
    for (uint8_t i = 0; i < 3; i++){
      retorn = retorn && ((box[i] % 2) == 0);
    }
  } else { // izquierda
    for (uint8_t i = 0; i < 3; i++){
      retorn = retorn && (box[i] < 128);
    }
  }
  
  return retorn;
}

void game_x_mov(Pieza *box){
  uint8_t i;
  uint8_t j;

  if (box->pos_x > 0) 
  {
    for (i = 0; i < box->pos_x; i++)
    {
      if (game_check_x_mov(box->form, true))
      { // mover el sprite
        for (j = 0; j < 3; j++){
          box->form[j] = box->form[j] >> 1; 
        }
      }else
      { // reasignar la posicion (era excesiva)
        box->pos_x = i;
        break;
      }
    }
  } else 
  {
    for (i = 0; i > box->pos_x; i--)
    {
      if (game_check_x_mov(box->form, false))
      { // mover el sprite
        for (j = 0; j < 3; j++){
          box->form[j] = box->form[j] << 1; 
        }
      }else
      { // reasignar la posicion (era excesiva)
        box->pos_x = i;
        break;
      }
    }
  }
}

bool game_check_hitbox(Pieza *hitbox){
  game_x_mov(hitbox);

  sprite box;

  copiar_sprite(&box, &hitbox->form);

  uint8_t pos_y = hitbox->pos_y;

  bool retorn = true;

  if(0 == pos_y)
  {
    retorn = retorn && ((leer_fila(1) & box[0]) == 0);

    retorn = retorn && ((leer_fila(0) & box[1]) == 0);

    retorn = retorn && (box[2] == 0);
  }
  else if (game.map_size - 1 == pos_y)
  {
    retorn = retorn && (box[0] == 0);

    retorn = retorn && ((leer_fila(game.map_size)     & box[0]) == 0);

    retorn = retorn && ((leer_fila(game.map_size - 1) & box[2]) == 0);
  }
  else{
    retorn = retorn && ((leer_fila(pos_y + 1) & box[0]) == 0);

    retorn = retorn && ((leer_fila(pos_y)     & box[1]) == 0);

    retorn = retorn && ((leer_fila(pos_y - 1) & box[2]) == 0);
  }

  return retorn;
}

// ======================================================================

bool game_new_piece(){
  Pieza *hitbox;
  Pieza *pieza;

  hitbox = &game.hitbox;
  pieza = &game.pieza;

  if(game.next != 7){

    borrar_sprite(27, PIEZAS[0][game.next]);

    copiar_sprite(&hitbox->form, &PIEZAS[0][game.next]);

  }else{
    copiar_sprite(&hitbox->form, &PIEZAS[0][random(7)]);
  }

  game.next = random(7);

  escribir_sprite(27, PIEZAS[0][game.next]);

  // preparar la hitbox
  hitbox->rot = 0;
  hitbox->pos_x = 0;
  hitbox->pos_y = game.map_size - 2;

  // preparar la pieza
  if (game_check_hitbox(&game.hitbox)){
    game.pieza = game.hitbox;
    escribir_sprite(pieza->pos_y, pieza->form);
  }
  else{
    return false; // GAME OVER
  }
  game.state = MOVEMENT;
  return true;
}

void game_movement(/*unsigned input*/){
  Pieza *hitbox;
  Pieza *pieza;

  hitbox = &game.hitbox;
  pieza = &game.pieza;

  // por rellenar

  if(game_check_hitbox(&game.hitbox)){

    borrar_sprite(pieza->pos_y, pieza->form);

    escribir_sprite(hitbox->pos_y, hitbox->form);

    game.pieza = game.hitbox;
  }else{
    if(false){
      // por rellenar
    }else{
      game.state = CHECKOUT;
    }
  }
}

void game_checkout(){
  for(uint8_t i = 0; i < game.map_size; i++){
    if(leer_fila(i) == 0b11111111)
    {
      escribir_fila(i, 0b00000000);

      game.state = FALL;
      return;
    }
  }
  game.state = NEW_PIECE;
}

void game_fall(){
  game.state = CHECKOUT;
  for(uint8_t i = 0; i < game.map_size; i++){
    if(leer_fila(i) == 0)
    {
      barrido_pantalla(i, game.map_size);
      break;
    }
  }
}

// ======================================================================

bool game_play(){
  static unsigned long prev = 0;
  unsigned long time = millis();

  if(time - prev >= game.inv_fps){
    prev = time;

    switch (game.state) {
      case CHECKOUT:
        game_checkout();
        break;

      case FALL:
        game_fall();
        break;

      case MOVEMENT:
        game_movement();
        break;

      case NEW_PIECE:
        return game_new_piece();
        break;

      default:
        game_checkout();
    }
  }
  return true;
}

void game_reset(){
  game.state = NEW_PIECE;
  game.next = 7;
  game.pieza = {{0,0,0}, 0, 0, 0, 0};
  game.hitbox = {{0,0,0}, 0, 0, 0, 0};
}

#endif