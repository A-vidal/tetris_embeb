#ifndef CONTROLES
#define CONTROLES

#include "Arduino.h"

typedef struct {
  int KEY = KEY_PIN;
  int JOYx = JOYx_PIN;
  int JOYy = JOYy_PIN;
} Pines ;

Pines pines
typedef struct {
  int direccion;
  bool doble;
  bool pulsar;
} Cursor ;

Cursor cursor;


bool KEY_read(){
  return (digitalRead(pines.KEY) == LOW);
}

int JOYx_read(){
  if (analogRead(pines.JOYx) > 550){
    return 1;
  }
  else if (analogRead(pines.JOYx) < 474){
    return -1;
  }
  else{
    return 0;
  }
}

bool JOYy_read(){
  return analogRead(pines.JOYy) > 600;
}

void joy_setup() {
  pinMode(pines.KEY, INPUT_PULLUP);
}

void informacion(){
  if (abs(cursor.direccion) > 3){
    cursor.direccion /= 2;
  }
  cursor.direccion += JOYx_read();
  cursor.doble = cursor.doble || JOYy_read();
  cursor.pulsar = cursor.pulsar || KEY_read();
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