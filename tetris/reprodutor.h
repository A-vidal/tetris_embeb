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

  int pin;
  note *melody;
} Track;

typedef struct {
  uint8_t current_track;

  uint8_t BPM;
  int8_t subdivision;
  unsigned long t_interval;

  unsigned long prev_time;

  uint8_t traks_len = 1;
  Track tracks[1];

} Player;

Player rep;

void rep_setup(){
  rep = {0, 140, 2, 0, 0, 1, [
  {0, 0, {0, 0, 0}, // Track
  8, // PIN Zumbador
  &tema_principal // Melodia
  }
  // Aqui se pueden añadir mas Tracks
  ]};
};

// ==================================================================================================================================

void rep_change_BPM(uint8_t BPM){
  rep.BPM = BPM;
  if (m_subdivision > 0)
    rep.t_interval = (60000 / BPM) >> rep.subdivision;
  else
    rep.t_interval = (60000 / BPM) << rep.subdivision;
};

void rep_test(unsigned long period){
  static unsigned long prev;

  unsigned long time = millis();

  if (time - prev >= period) {
    prev = time;

    for (uint8_t i = 0; i <= current_track; i++) {
      static bool tone_state;
      if (tone_state) {
        tone_state = false;
        noTone(rep.trakcs[i].pin);
      } else {
        tone_state = true;
        tone(rep.trakcs[i].pin, 440);
      }
    }
  }
};

void rep_play(){
  static unsigned long prev;
  unsigned long time = millis();

  if (time - prev >= t_interval) {
    prev = time;

    for (uint8_t i = 0; i < rep.current_track; i++) {
      // Copiar Track ===============================
      uint8_t *elong_left = &rep.trakcs[i].elong_left;
      uint8_t *step = &rep.trakcs[i].step;
      note *nota_actual = &rep.trakcs[i].nota_actual;

      const int pin = rep.trakcs[i].pin;
      const note *melody = rep.trakcs[i].melody;
      // ============================================

      if (elong_left < 1) {
        nota_actual = melody[step];

        if (nota_actual->elongacion == 0)  // fin de melodia -> Repetir Bucle
        {
          step = 0;
          nota_actual = melody[step];
        }

        elong_left = nota_actual->elongacion;

        if (nota_actual->tesitura > 0)  // Nota
        {
          // unsigned long duracion = player_period * elong_left;
          int freq = nota_to_freq(nota_actual->nota, nota_actual->tesitura);
          tone(pin, freq);
          // tone(pin, freq, duracion);
        } else { // Silencio
          noTone(pin);
        }

        step++;

      } else {
        elong_left--;
      }
    }
  }
};


void stop(){
  for (uint8_t i = 0; i < current_track; i++) {
    // Copiar Track ===============================
    uint8_t *elong_left = &rep.trakcs[i].elong_left;
    uint8_t *step = &rep.trakcs[i].step;

    const int pin = rep.trakcs[i].pin;
    // ============================================

    noTone(pin);
    elong_left = 0;
    step = 0;
  }
  this->prev_time = 0;
};

#endif