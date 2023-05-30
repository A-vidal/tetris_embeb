#ifndef CONTROLES
#define CONTROLES

#include "Arduino.h"

bool KEY_read() {
  return digitalRead(KEY) == LOW;
}

void KEY_interr(){
  static unsigned long previous = 0;
  unsigned long time = millis();

  if(time - previous >= react_time){
    previous = time;

    // INTRODUCIR CODIGO
  }
}

void joy_setup() {
  pinMode(KEY, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(KEY), KEY_interr, RISING);
}

#endif