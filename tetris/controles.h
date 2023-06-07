#ifndef CONTROLES
#define CONTROLES

#include "Arduino.h"

typedef struct {
  int KEY;
  int JOYx;
  int JOYy;
} Pines ;

typedef struct {
  int direccion;
  bool doble;
  bool pulsar;
} Cursor ;

Cursor cursor;

Pines pin;

void controles_setup(int KEY, int JOYx, int JOYy){
  pin.KEY = KEY;
  pin.JOYx = JOYx;
  pin.JOYy = JOYy;
  pinMode(pin.KEY, INPUT_PULLUP);
}

bool KEY_read(){
  return (digitalRead(pin.KEY) == LOW);
}

int JOYx_read(){
  if (analogRead(pin.JOYx) > 600){
    return 1;
  }
  else if (analogRead(pin.JOYx) < 400){
    return -1;
  }
  else{
    return 0;
  }
}

bool JOYy_read(){
  return analogRead(pin.JOYy) > 600;
}

void informacion(){
  cursor.doble = cursor.doble || JOYy_read();
  cursor.pulsar = cursor.pulsar || KEY_read();

  int J = JOYx_read();

  if (J != 0){
    cursor.direccion = J;
  }
}

bool get_KEY(){
  bool retorn = cursor.pulsar;
  cursor.pulsar = false;
  return retorn;
}

bool get_JOYy(){
  bool retorn = cursor.doble;
  cursor.doble = false;
  return retorn;
}

int get_JOYx(){
  int retorn = cursor.direccion;
  cursor.direccion = 0;
  return retorn;
}

#endif