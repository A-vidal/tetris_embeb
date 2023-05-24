#include "musica.h"
#include "reproductor.h"

using namespace rep;

const int pinZumb = 8;

Player player;

void setup()
{
  pinMode(pinZumb, OUTPUT);
  Serial.begin(115200);

  player.set_subdivision(2);
  player.change_BPM(140);
  Serial.print(tema_principal[0].nota);
  Serial.print(tema_principal[0].tesitura);
  Serial.println(tema_principal[0].elongacion); // BORRAR
  player.add_track(pinZumb, tema_principal);

  // Test
  tone(pinZumb, 440);
  delay(1000);
  noTone(pinZumb);
}

void loop()
{
  player.play();
  // Serial.println(" >loop");
  delay(5); // control
}