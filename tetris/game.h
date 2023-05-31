#include <stdint.h>
#ifndef GAME
#define GAME

#include "Arduino.h"
#include "sprites.h"

enum game_fase{
  NEW_PIECE, MOVEMENT, CHECKOUT, FALL
}

typedef struct {
  sprite form;
  int8_t pos_x; // posicion % 8
  uint8_t pos_y; // posicion % map_size
  uint8_t rot; // rotacion % 4
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

  if (rignt) { // derecha
    for (uint8_t i = 0; i < 3, i++){
      retorn = retorn && ((box[i] % 2) == 0)
    }
  } else { // izquierda
    for (uint8_t i = 0; i < 3, i++){
      retorn = retorn && (box[i] < 128)
    }
  }
  
  return retorn;
}

sprite game_x_mov(Pieza *box){
  sprite retorn = box->form;

  uint8_t i;
  uint8_t j;

  if (x > 0) 
  {
    for (i = 0; i < x, i++)
    {
      if (game_check_x_mov(retorn, true))
      { // mover el sprite
        for (j = 0; j < 3, j++){
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
    for (uint8_t i = 0; i > x, i--)
    {
      if (game_check_x_mov(retorn, false))
      { // mover el sprite
        for (j = 0; j < 3, j++){
          retorn = retorn << 1; 
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
  sprite box = game_x_mov(hitbox);

  uint8_t pos_y = hitbox->pos_y;

  bool retorn = true

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
}

void gameover(){}

// ======================================================================

void game_new_peace(){
  Pieza *pieza = &game.pieza;
  Pieza *hitbox = &game.hitbox;

  sprite forma = PIEZAS[0][random(7)];

  hitbox->rot = 0;
  hitbox->pos_x = 0;
  hitbox->pos_y = game.map_size - 1;

  hitbox->form = forma

  if (game_check_hitbox(hitbox)){
    gameover();
  }
}

// ======================================================================

void game_play(unsigned input){
  static unsigned long prev = 0;
  unsigned long time = millis();

  if(time - prev >= game.inv_fps){
    prev = time;

    switch (game.fase) {
      case NEW_PIECE:
        game_new_peace();
        break;
      case DIRECTION:
        
    }
  }
}



#endif