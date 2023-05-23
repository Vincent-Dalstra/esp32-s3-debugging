#include <Arduino.h>

#include "esp32-hal.h"


void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  Serial.println("Hello world!");
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  neopixelWrite(LED_BUILTIN, 255, 0, 0);
  delay(500);
  neopixelWrite(LED_BUILTIN, 0, 255, 0);
  delay(500);
  neopixelWrite(LED_BUILTIN, 0, 0, 255);
  delay(500);
}

