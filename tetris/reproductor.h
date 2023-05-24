#ifndef REPRODUCTOR
#define REPRODUCTOR

#include "Arduino.h"
#include "musica.h"
#include <stdint.h>

int elongacion_to_duracion(uint8_t elong, int t_ref) {
  t_ref *= elong;
  int duracion = t_ref;  // semicorchera
  return duracion;
}

int nota_to_freq(const uint8_t nota, const uint8_t tesitura) {
  if (tesitura < 1) {
    return 0;
  }

  uint8_t diff_tes = (tesitura - 4);

  int frecuencia = (diff_tes >= 0) ? (NOTES[nota] << diff_tes) : (NOTES[nota] >> abs(diff_tes));

  return frecuencia;
}

//==============================================================================================================

typedef struct {
  uint8_t elong_left;
  uint8_t step;
  note nota_actual;
} Player;

typedef struct {
  int pin;
  note *melody;

  uint8_t BPM;
  int8_t subdivision;
  unsigned long t_interval;
  Player player;
} Reproductor;

Reproductor rep;

void rep_change_BPM(uint8_t BPM){
  rep.BPM = BPM;
  if (rep.subdivision > 0)
    rep.t_interval = (60000 / BPM) >> rep.subdivision;
  else
    rep.t_interval = (60000 / BPM) << rep.subdivision;
};

void rep_setup(int pin, const note *melody, uint8_t BPM, int8_t subdivision){
  Player player = {0, 0, melody[0]};

  rep.pin = pin;
  rep.melody = melody;
  rep.subdivision = subdivision;
  rep.player = player;

  rep_change_BPM(BPM);

  pinMode(pin, OUTPUT);
};

// ==================================================================================================================================

void rep_test(unsigned long period){
  static unsigned long prev;
  static bool tone_state;

  unsigned long time = millis();

  if (time - prev >= period) {
    prev = time;

    if (tone_state) {
      tone_state = false;
      noTone(rep.pin);
    } else {
      tone_state = true;
      tone(rep.pin, 440);
    }
  }
};

void rep_play(){
  static unsigned long prev;
  unsigned long time = millis();

  if (time - prev >= rep.t_interval) {
    prev = time;

    note nota_actual = rep.player.nota_actual;

    if (rep.player.elong_left < 1) {
      nota_actual = rep.melody[rep.player.step];

      if (nota_actual.elongacion == 0)  // fin de melodia -> Repetir Bucle
      {
        rep.player.step = 0;
        nota_actual = rep.melody[rep.player.step];
      }

      rep.player.elong_left = nota_actual.elongacion;

      if (nota_actual.tesitura > 0)  // Nota
      {
        // unsigned long duracion = player_period * elong_left;
        int freq = nota_to_freq(nota_actual.nota, nota_actual.tesitura);
        tone(rep.pin, freq);
        // tone(pin, freq, duracion);
      } else { // Silencio
        noTone(rep.pin);
      }

      rep.player.step++;

    } else {
      rep.player.elong_left--;
    }
  }
};


void stop(){
  noTone(rep.pin);
  rep.player.elong_left = 0;
  rep.player.step = 0;
};

#endif