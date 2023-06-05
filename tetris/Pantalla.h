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
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

//Iniciar pantalla
void MD_setup() {
  mx.begin();
  resetMD();
}

// Funciones

uint8_t leer_fila(uint8_t i){
  return mx.getColumn(i);
}

void escribir_fila(uint8_t i, uint8_t value){
  mx.setColumn(i, value);
}

void escribir_sprite(uint8_t i, sprite form){
  mx.setColumn(i+1, form[0]);
  mx.setColumn(i, form[1]);
  if (i>0)
    mx.setColumn(i-1, form[2]);
}

void borrar_sprite(uint8_t i, sprite form){
  for(uint8_t k= 0; k < 3, k++){
    form[k] = form[k] ^ 0b11111111
  }
  mx.setColumn(i+1, form[0]);
  mx.setColumn(i, form[1]);
  if (i>0)
    mx.setColumn(i-1, form[2]);
}

void barrido_pantalla(uint8_t i, uint8_t max){
  uint8_t value;
  for(uint8_t k = i; k < max; k++){
    if (k + 1 == max){
      value = 0
    }else{
      value = mx.getColumn(k);
    }
    mx.setColumn(k, value);
  }
}

#endif
