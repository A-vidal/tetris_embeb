#ifndef CONTROLES
#define CONTROLES

#include "Arduino.h"

typedef struct {
  unsigned KEY state;
  unsigned JOYx state;
  unsigned JOYy state;
  int direccion;
  int ejex;
  bool ejey;
  bool pulsar;
} Cursor ;

Cursor cursor

bool KEY_read() {
  return digitalRead(cursor.KEY) == LOW;
}

void JOYx_read(){
  if (analogRead(cursor.JOYx) > 550){
    return cursor.direccion = 2;
  }
  else if (analogRead(cursor.JOYx) > 474){
    return cursor.direccion = 1;
  }
  else{
    return cursor.direccion = 0;
  }
}

void JOYy_read(){
  return analogRead(cursor.JOYy) > 550;
}

void joy_setup() {
  pinMode(cursor.KEY, INPUT_PULLUP);
}

void informacion(){
  cursor.ejex = JOYx_read();
  cursor.ejey = JOYy_read();
  cursor.pulsar = KEY_read();
}

#endif