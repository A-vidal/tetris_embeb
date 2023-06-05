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
  Pieza pieza;
  Pieza hitbox;
  uint8_t map_size;
} Game;

Game game;

uint8_t game_map[24];

// =======================================================================

void game_setup(uint8_t FPS, uint8_t map_size = 24){
  game.inv_fps = 1000 / FPS
  game.state = NEW_PIECE;
  game.map_size = map_size;
}

void game_change_FPS(uint8_t FPS){
  game.inv_fps = 1000 / FPS
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

sprite game_x_mov(Pieza *box){
  sprite retorn = PIEZAS[box->rot][box->num];

  uint8_t i;
  uint8_t j;

  if (box->pos_x > 0) 
  {
    for (i = 0; i < box->pos_x; i++)
    {
      if (game_check_x_mov(retorn, true))
      { // mover el sprite
        for (j = 0; j < 3; j++){
          retorn = retorn >> 1; 
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
      if (game_check_x_mov(retorn, false))
      { // mover el sprite
        for (j = 0; j < 3; j++){
          retorn = retorn << 1; 
        }
      }else
      { // reasignar la posicion (era excesiva)
        box->pos_x = i;
        break;
      }
    }
  }
  return retorn;
}

bool game_check_hitbox(Pieza *hitbox){
  sprite box = game_x_mov(hitbox);

  uint8_t pos_y = hitbox->pos_y;

  bool retorn = true;

  if(0 == pos_y)
  {
    retorn = retorn && ((game_map[1] & box[0]) == 0);

    retorn = retorn && ((game_map[0] & box[1]) == 0);

    retorn = retorn && (box[2] == 0);
  }
  else if (game.map_size == pos_y)
  {
    retorn = retorn && (box[0] == 0);

    retorn = retorn && ((game_map[game.map_size]     & box[0]) == 0);

    retorn = retorn && ((game_map[game.map_size - 1] & box[2]) == 0);
  }
  else{
    retorn = retorn && ((game_map[pos_y + 1] & box[0]) == 0);

    retorn = retorn && ((game_map[pos_y]     & box[1]) == 0);

    retorn = retorn && ((game_map[pos_y - 1] & box[2]) == 0);
  }

  return retorn;
}

// ======================================================================

bool game_new_piece(){
  Pieza *pieza = &game.pieza;
  Pieza *hitbox = &game.hitbox;

  sprite forma = PIEZAS[0][random(7)];

  hitbox->rot = 0;
  hitbox->pos_x = 0;
  hitbox->pos_y = game.map_size - 2;

  hitbox->form = forma;

  if (game_check_hitbox(hitbox)){
    pieza = *hitbox;
    // map_print()
    game_map[pieza->pos_y + 1] = pieza->form[0];
    game_map[pieza->pos_y ] = pieza->form[1];
    game_map[pieza->pos_y - 1] = pieza->form[2];
  }
  else{
    return false; // GAME OVER
  }
  game.state = MOVEMENT;
}

void game_movement(unsigned input){
  Pieza *pieza = &game.pieza;
  Pieza *hitbox = &game.hitbox;

  // por rellenar

  if(game_check_hitbox(hitbox)){

  }else{
    if(input){
      // por rellenar
    }else{
      game.state = CHECKOUT;
    }
  }
}

void game_checkout(){
  for(uint8_t i = 0; i < game.map_size; i++){
    if(game_map[i] == 0b11111111)
    {
      game_map[i] = 0;

      game.state = FALL;
      return;
    }
  }
  game.state = NEW_PIECE;
}

void game_fall(){
  game.state = CHECKOUT;
  for(uint8_t i = 0; i < game.map_size; i++){
    if(game_map[i] == 0)
    {
      barrido_pantalla(i, game.map_size);
      break;
    }
  }
}

// ======================================================================

bool game_play(unsigned input){
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
    return true;
  }
}



#endif