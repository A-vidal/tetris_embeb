#ifndef CONTROLES
#define CONTROLES

#include "Arduino.h"

typedef struct {
  int direccion;
  bool doble;
  bool pulsar;
} Cursor ;

Cursor cursor;

bool KEY_read() {
  return (digitalRead(KEY_PIN) == LOW);
}

int JOYx_read(){
  if (analogRead(JOYx_PIN) > 550){
    return 1;
  }
  else if (analogRead(JOYx_PIN) < 474){
    return -1;
  }
  else{
    return 0;
  }
}

bool JOYy_read(){
  return analogRead(JOYy_PIN) > 600;
}

void joy_setup() {
  pinMode(KEY_PIN, INPUT_PULLUP);
}

void informacion(){
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