#include "musica.h"
#include "reproductor.h"

const int pinZumb = 8;

void setup()
{
  pinMode(pinZumb, OUTPUT);
  Serial.begin(115200);

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