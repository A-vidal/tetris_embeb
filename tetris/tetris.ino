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

uint8_t FPS = 15 // Ejecuciones de la pantalla por segundo

void setup()
{
  Serial.begin(115200);

  rep_setup(pinZumb, tema_principal, 160, 2);
}

void loop()
{
  rep_play();
  // Serial.println(" >loop");
}