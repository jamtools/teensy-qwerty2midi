#include "MyLogic.h"
#include "ArduinoHardware.h"

ArduinoHardware hardware;
MyLogic logic(hardware);

void setup() {
  Serial.begin(9600);
  logic.setup();
}

void loop() {
  usbMIDI.read();
  logic.loop();
  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(500);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(100);                      // wait for a second
}
