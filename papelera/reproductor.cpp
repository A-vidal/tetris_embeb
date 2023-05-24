#include "Arduino.h"
#include "reproductor.h"
#include "musica.h"
#include <stdint.h>

using namespace rep;

int rep::elongacion_to_duracion(uint8_t elong, int t_ref) {
  t_ref *= elong;
  int duracion = t_ref;  // semicorchera
  return duracion;
}

int rep::nota_to_freq(const uint8_t nota, const uint8_t tesitura) {
  if (tesitura < 1) {
    return 0;
  }

  uint8_t diff_tes = (tesitura - 4);

  int frecuencia = (diff_tes >= 0) ? (NOTES[nota] << diff_tes) : (NOTES[nota] >> abs(diff_tes));

  return frecuencia;
}

//  TRACK _____________________________________________________________________________________

Track::Track() {
  elong_left = 0;
};

void Track::set_pin(int pin) {
  m_pin = pin;
};

void Track::set_melody(const note melody[]) {
  m_melody = melody;
  Serial.println((unsigned long)&m_melody, HEX);
  nota_actual = m_melody[0];
};

void Track::test(int freq) {
  static bool tone_state;
  if (tone_state) {
    tone_state = false;
    noTone(m_pin);
  } else {
    tone_state = true;
    tone(m_pin, freq);
  }
};

void Track::play() {
  /*
  Serial.print((unsigned long)m_melody, HEX);
  Serial.print("; ");
  */
  Serial.print((unsigned long)tema_principal, HEX);
  Serial.print("; ");
  
  Serial.print((unsigned long)&elong_left, HEX);
  Serial.print("; ");
  Serial.print((unsigned long)this, HEX);
  Serial.print("; ");
  Serial.print(step);
  Serial.print("; ");
  Serial.print(this->elong_left);
  Serial.print("; ");
  Serial.print(nota_actual.nota);
  Serial.print(", ");
  Serial.print(nota_actual.tesitura);
  Serial.print(", ");
  Serial.println(nota_actual.elongacion);

  if (elong_left < 1) {
    nota_actual = m_melody[step];

    if (nota_actual.elongacion == 0)  // fin de melodia -> Repetir Bucle
    {
      step = 0;
      nota_actual = m_melody[step];
    }

    elong_left = nota_actual.elongacion;

    if (nota_actual.tesitura > 0)  // Nota
    {
      // unsigned long duracion = player_period * elong_left;
      int freq = nota_to_freq(nota_actual.nota, nota_actual.tesitura);
      tone(m_pin, freq);
      // tone(pin, freq, duracion);
    } else { // Silencio
      noTone(m_pin);
    }

    step++;

  } else {
    Serial.println(elong_left);
    elong_left--;
    Serial.println(elong_left);
  }
};

void Track::stop() {
  noTone(m_pin);
  elong_left = 0;
  step = 0;
};

// PLAYER _______________________________________________________________________________

void Player::set_subdivision(int8_t subdivision) {
  m_subdivision = subdivision;
}

void Player::change_BPM(uint8_t BPM) {
  m_BPM = BPM;
  if (m_subdivision > 0)
    t_interval = (60000 / BPM) >> m_subdivision;
  else
    t_interval = (60000 / BPM) << m_subdivision;
};

Player::Player() {
  tracks[1];
  traks_len = 1;
};

void Player::add_track(uint8_t pin, const note melody[]) {
  if (current_track < traks_len) {
    Track track;
    track.set_pin(pin);
    track.set_melody(melody);
    tracks[current_track] = track;
    current_track++;
    return false;
  } else {
    return true;
  }
};

void Player::test(unsigned long period = (60000 / 140)) {
  static unsigned long prev;

  unsigned long time = millis();

  if (time - prev >= period) {
    prev = time;

    for (uint8_t i = 0; i <= current_track; i++) {
      tracks[i].test(440);
    }
  }
};

void Player::play() {
  unsigned long time = millis();

  if (time - prev_time >= t_interval) {
    prev_time = time;

    for (uint8_t i = 0; i < current_track; i++) {
      tracks[i].play();
    }
  }
};

void Player::stop() {
  for (uint8_t i = 0; i < current_track; i++) {
    tracks[i].stop();
  }
  this->prev_time = 0;
};

Player* rep::setup_player() {
  Player x;
  return &x;
};
