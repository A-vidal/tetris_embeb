#include "musica.h"
#include "reproductor.h"
#include "Pantalla.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 13   // or SCK
#define DATA_PIN 11  // or MOSI
#define CS_PIN 10    // or SS

#define KEY 4
#define JOYx A0
#define JOYy A1

const int pinZumb = 8;

void setup()
{
  pinMode(pinZumb, OUTPUT);
  Serial.begin(115200);

  MD_MAX72XX_setup(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES)
  rep_setup();

  // Test
  tone(pinZumb, 440);
  delay(1000);
  noTone(pinZumb);
}

void loop()
{
  rep_play();
  // Serial.println(" >loop");
  delay(5); // control
}