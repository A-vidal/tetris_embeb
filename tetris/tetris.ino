#define KEY 4
#define JOYx A0
#define JOYy A1

#define ZUMB_PIN 8

#define CLK_PIN 13   // or SCK
#define DATA_PIN 11  // or MOSI
#define CS_PIN 10    // or SS

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#include "controles.h"
#include "musica.h"
#include "reproductor.h"
#include "Pantalla.h"
#include "game.h"

uint8_t FPS = 15; // Ejecuciones de la pantalla por segundo

bool play;

void setup()
{
  Serial.begin(115200);

  rep_setup(ZUMB_PIN, tema_principal, 120, 3);

  MD_setup();

  pantalla_inicio();
}

void loop()
{
  informacion();
  if(play){
    rep_play();

    play = game_play();

    if(!play){
      rep_stop();

      game_reset();

      resetMD();
      pantalla_inicio();
    }

  }else{

    play = get_KEY();

    if(play){
      resetMD();
      for (uint8_t i = 0; i < 8; i++) {
        escribir_fila(31-i, CUADRADO_JUEGO[i]);
      }
    }
  }
  // Serial.println(" >loop");
}

