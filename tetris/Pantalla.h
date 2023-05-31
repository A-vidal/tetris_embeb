#ifndef PANTALLA
#define PANTALLA

#include "Arduino.h"
#include "sprites.h"
#include <MD_MAX72xx.h>


typedef struct{
    unsigned HARDWARE_TYPE state;
    unsigned DATA_PIN state;
    unsigned CLK_PIN state;
    unsigned CS_PIN state;
    unsigned MAX_DEVICES state;
    unsigned long react_time = 50;//miliseconds
} Pantalla;

Pantalla pantalla

#define ROW_SIZE 8  // tamaño del modulo
#define COL_SIZE (MAX_DEVICES * ROW_SIZE)

//Ajustes pantalla
void MD_MAX72XX_setup(pantalla.HARDWARE_TYPE, pantalla.DATA_PIN, pantalla.CLK_PIN, pantalla.CS_PIN, pantalla.MAX_DEVICES){
    MD_MAX72XX mx = MD_MAX72XX(pantalla.HARDWARE_TYPE, pantalla.DATA_PIN, pantalla.CLK_PIN, pantalla.CS_PIN, pantalla.MAX_DEVICES);
}

uint8_t screen[COL_SIZE];

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

//Modos

void mode_inicio() {
    PANTALLA_INICIO[0];

}

void mode_jugar(){
    CUADRADO_JUEGO[0];
    
    
}

void setup() {
  MD_setup()
  mode_inicio();
}

#endif
