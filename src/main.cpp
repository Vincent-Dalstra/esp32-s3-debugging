#include <Arduino.h>

#include "esp32-hal.h"


// Only Dev boards have the Built-in LED.
#define SIMPLE true

#if SIMPLE == false
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

#elif SIMPLE == true

bool trueDelay(int millis);

TickType_t xLastWakeTime;
BaseType_t xWasDelayed;

void setup()
{
  Serial.begin(115200);

  pinMode(15, OUTPUT);    // One of the relays on the ESP32-S3-2R board, just to test with.
  pinMode(16, OUTPUT);    // Other Relay. Both relays have indicator LED's as well.
  xLastWakeTime = xTaskGetTickCount();
}

void loop()
{ 
  while (true)
  {
    
    Serial.println("Hello world!");

    //digitalWrite(LED_BUILTIN, LOW);
    //delay(500);
    digitalWrite(15, HIGH);
    delay(5000);              // Uses vTaskDelay()
    digitalWrite(15, LOW);
    vTaskDelay(5000);         // Uses vTaskDelay()
    digitalWrite(16, HIGH);
    trueDelay(5000);          // Uses vTaskDelayUntil()
    digitalWrite(16, LOW);
    delayMicroseconds(5000 * 1000);   // This works properly, becaue it uses busy-waiting instead of yielding (and involving the task scheduler)
  }
}

/*  So to just get across how weird this problem is...
 *  - Time spent in the debugger counts against any calls to vTaskDelay() thereafter...
 *  - It is cumulative in both directions! If the time exceeds the next delay(), the remainder
 *    will carry over to the delay() after that, and so on.
 *
 *  - Applies to vTaskDelayUntil() as well.
 *    - EVEN WHEN YOU EXPLICITLY PASS IT THE TIME
 *      - (You're supposed to pass it a pointer and let it increment on its own)
 *      - See code below.
 */



bool trueDelay(int millis)
{
  TickType_t start = xTaskGetTickCount();
  TickType_t ticks = (millis / portTICK_PERIOD_MS);
  return xTaskDelayUntil( &start, ticks );          // Suffers the same issue as vTaskDelay();
}


#endif