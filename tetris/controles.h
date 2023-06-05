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
  return (digitalRead(KEY) == LOW);
}

int JOYx_read(){
  if (analogRead(JOYx) > 550){
    return 1;
  }
  else if (analogRead(JOYx) < 474){
    return -1;
  }
  else{
    return 0;
  }
}

bool JOYy_read(){
  return analogRead(JOYy) > 600;
}

void joy_setup() {
  pinMode(KEY, INPUT_PULLUP);
}

void informacion(){
  cursor.direccion += JOYx_read();
  cursor.doble = cursor.doble || JOYy_read();
  cursor.pulsar = cursor.pulsar || KEY_read();
}

bool get_KEY(){
  return cursor.pulsar;
}

bool get_JOYy(){
  return cursor.doble;
}

int get_JOYx(){
  return cursor.direccion;
}

#endif