#include "musica.h"
#include "reproductor.h"

const int pinZumb = 8;

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