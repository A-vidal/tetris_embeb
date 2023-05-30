#ifndef GAME
#define GAME

#include "Arduino.h"

enum game_fase{
  DIRECTION ,HITBOX, MOVEMENT, CHECKOUT, FALL, NEW_PIECE
}

typedef struct {
  unsigned long inv_fps;
  game_fase state;

} Game;

Game game;

void game_setup(uint8_t FPS){
  game.inv_fps = 1000 / FPS
}

void game_change_FPS(uint8_t FPS){
  game.inv_fps = 1000 / FPS
}

void game_play(unsigned input){
  static unsigned long prev = 0;
  unsigned long time = millis();

  if(time - prev >= game.inv_fps){
    prev = time;

    // INTRODUCIR CODIGO
  }
}



#endif