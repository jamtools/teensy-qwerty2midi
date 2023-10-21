#include "MyLogic.h"
#include "ArduinoHardware.h"

ArduinoHardware hardware;
MyLogic logic(hardware);

void setup() {
  logic.setup();
}

void loop() {
  logic.loop();
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(10000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
