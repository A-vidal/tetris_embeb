#ifndef PANTALLA
#define PANTALLA

#include "Arduino.h"
#include "sprites.h"
#include <MD_MAX72xx.h>

typedef struct{
    uint8_t orientation;
    sprite form;
    int8_t position;
} pieza;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 13   // or SCK
#define DATA_PIN 11  // or MOSI
#define CS_PIN 10    // or SS

#define ROW_SIZE 8  // tamaño del modulo
#define COL_SIZE (MAX_DEVICES * ROW_SIZE)

#define KEY 4
#define JOYx A0
#define JOYy A1

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


unsigned long react_time = 50; // miliseconds

struct curs {
  uint8_t x;
  uint8_t y;
  bool state;
};

curs cursor = { 0, 0, false };

uint8_t screen[COL_SIZE];

void resetMD() {
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void MD_setup() {
  mx.begin();
  resetMD();
}

void joy_setup() {
  pinMode(KEY, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(KEY), KEY_interr, RISING);
}

bool KEY_read() {
  return digitalRead(KEY) == LOW;
}

void KEY_interr(){
  static unsigned long previous = 0;
  unsigned long time = millis();

  if(time - previous >= react_time){
    cursor_change();

    previous = time;
  }
}

uint8_t joy_interr(uint8_t input, int value){
  static unsigned long previous = 0;
  unsigned long time = millis();

  if(abs(value) > 16){
    previous = 0;
  }else{

    unsigned long time = (value << 3); 

    if(millis() - previous >= time)
    {
      input++;
      previous = time;
    }
  }

  return input;
}

curs joystick() {
  static unsigned long previous_x = 0;
  static unsigned long previous_y = 0;

  int x = analogRead(JOYx) - 512; 
  int y = analogRead(JOYy) - 512; 

  uint8_t cx = cursor.x;
  uint8_t cy = cursor.y;

  unsigned long time_interval;
  unsigned long total = millis();

  if(abs(x) < 24){previous_x = total;}
  else{
    time_interval = (512 >> (abs(x) >> 7)); 
    if(total - previous_x >= time_interval){
      if(x < 0){
        cx--;
      }else{
        cx++;
      }
      previous_x = total;
    }
  }

  if(abs(y) < 24){previous_y = total;}
  else{
    time_interval = (512 >> (abs(y) >> 7)); 
    if(total - previous_y >= time_interval){
      if(y < 0){
        cy--;
      }else{
        cy++;
      }
      previous_y = total;
    }
  }

  cx = cx % ROW_SIZE;
  cy = cy % COL_SIZE;


  return { cx, cy, (cx != cursor.x || cy != cursor.y) };
}

/* 
escribe y BORRA en la memoria local de la pantalla (screen)
segun la posicion del cursor (NO IMPRIME NADA)
*/
void cursor_change() {
  cursor.state = !(cursor.state);

  uint8_t val = 1;
  screen[cursor.y] ^= (val << cursor.x);
}

void cursor_high() {
  cursor.state = true;

  uint8_t val = 1;
  screen[cursor.y] |= (val << cursor.x);
}

void cursor_low() {
  cursor.state = false;

  uint8_t val = 1;
  screen[cursor.y] &= !(val << cursor.x);
}

void cursor_move(uint8_t x, uint8_t y) {
  mx.setPoint(cursor.x, cursor.y, cursor.state);

  cursor.state = mx.getPoint(x, y);

  cursor.x = x;
  cursor.y = y;
}


/*
Copia en la pantalla la memoria local Screen
*/
void print_screen() {
  mx.clear();
  bool val;
  for (uint8_t x; x < ROW_SIZE; x++) {
    for (uint8_t y; y < COL_SIZE; y++) {
      val = (screen[y] & (1 << x)) > 0;
      mx.setPoint(x, y, val);
    }
  }
}

void setup() {
  Serial.begin(115200);

  MD_setup();

  joy_setup();

  cursor = { 2, 3, false };
}

//Loop por modificar entero, solo para referencia
void loop() {
  
  if(movimiento){
    mode_mov();
  }else{
    if(pintar){
      mode_pint();
    }else{
      mode_borr();
    }
  }

  if(KEY_read()){
    cursor_change();
  }

  curs change = joystick();

  if (change.state) {
    cursor_move(change.x, change.y);
  }

  Serial.print(cursor.x);
  Serial.print(", ");
  Serial.print(cursor.y);
  Serial.print(", ");
  Serial.print(cursor.state);
  Serial.print("\n");

  delay(50);
}


// void loop() {
  
//   if(movimiento){
//     mode_mov();
//   }else{
//     if(pintar){
//       mode_pint();
//     }else{
//       mode_borr();
//     }
//   }

//   if(KEY_read()){
//     cursor_change();
//   }

//   curs change = joystick();

//   if (change.state) {
//     cursor_move(change.x, change.y);
//   }

//   Serial.print(cursor.x);
//   Serial.print(", ");
//   Serial.print(cursor.y);
//   Serial.print(", ");
//   Serial.print(cursor.state);
//   Serial.print("\n");

//   delay(50);
// }

#endif
