#ifndef PANTALLA
#define PANTALLA

#include "Arduino.h"
#include "sprites.h"
#include <MD_MAX72xx.h>

#define ROW_SIZE 8  // tamaño del modulo
#define COL_SIZE (MAX_DEVICES * ROW_SIZE)

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

//Limpiar pantalla
void resetMD() {
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 8);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

//Iniciar pantalla
void MD_setup() {
  mx.begin();
  resetMD();
}

void pantalla_inicio(){
  for(uint8_t k = 0; k < 32; k++){
    mx.setColumn(k, PANTALLA_INICIO[31-k]);
  }
}

// Funciones

uint8_t leer_fila(uint8_t i){
  return mx.getColumn(i);
}

void escribir_fila(uint8_t i, uint8_t value){
  mx.setColumn(i, value);
}

void escribir_sprite(uint8_t i, const sprite form){
  sprite pantalla = {mx.getColumn(i+1), mx.getColumn(i), mx.getColumn(i-1)};
  sprite box;
  for(uint8_t k = 0; k < 3; k++){
    box[k] = form[k] | pantalla[k];
  }
  mx.setColumn(i+1, box[0]);
  mx.setColumn(i, box[1]);
  if (i>0)
    mx.setColumn(i-1, box[2]);
}

void borrar_sprite(uint8_t i, const sprite form){
  sprite pantalla = {mx.getColumn(i+1), mx.getColumn(i), mx.getColumn(i-1)};
  sprite box;
  for(uint8_t k = 0; k < 3; k++){
    box[k] = pantalla[k] & (~form[k]);
  }
  mx.setColumn(i+1, box[0]);
  mx.setColumn(i, box[1]);
  mx.setColumn(i-1, box[2]);
}

void barrido_pantalla(uint8_t i, uint8_t max){
  uint8_t value;
  for(uint8_t k = i; k < max; k++){
    if (k + 1 == max){
      value = 0b00000000;
    }else{
      value = mx.getColumn(k + 1);
    }
    mx.setColumn(k, value);
  }
}

#endif
