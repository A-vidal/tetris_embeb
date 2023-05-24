#ifndef REPRODUCTOR
#define REPRODUCTOR

#include "musica.h"
#include <stdint.h>

namespace rep
{
  int elongacion_to_duracion(uint8_t elong, int t_ref);

  int nota_to_freq(const uint8_t nota, const uint8_t tesitura);

  class Track 
  {
    uint8_t elong_left;
    uint8_t step;
    note nota_actual;

    public:

    int m_pin;
    const note *m_melody;

    Track();

    void set_pin(int para);

    void set_melody(const note melody[]);

    void test(int freq);

    void play();

    void stop();
  };

  class Player
  {
    unsigned long prev_time;

    public:

    uint8_t traks_len;
    uint8_t current_track;

    uint8_t m_BPM;
    int8_t m_subdivision;
    unsigned long t_interval;

    Track *tracks;

    Player();

    void change_BPM(uint8_t BPM);

    void set_subdivision(int8_t subdivision);

    void add_track(uint8_t pin, const note melody[]);

    void test(unsigned long period);

    void play();

    void stop();
  };

  Player* setup_player();
}

#endif