#include "ArduinoHardware.h"
#include "usb_dev.h"
#include "usb_names.h"
#include "core_pins.h"
#include "HardwareSerial.h"
#include "usb_serial.h"
#include <MIDI.h>

ArduinoHardware* ArduinoHardware::instance = nullptr;

ArduinoHardware::ArduinoHardware() {
    instance = this;
}

void ArduinoHardware::setupMIDI() {
    // Teensy MIDI usually does not require explicit initialization
}

void ArduinoHardware::sendMIDI(int note, int velocity) {
    usbMIDI.sendNoteOn(note, velocity, 1);  // Send NoteOn message on channel 1
}

void ArduinoHardware::sendSysEx(int length, const byte* data) {
    usbMIDI.sendSysEx(length, data);
}

void ArduinoHardware::setHandleSysEx(void (*handle)(const uint8_t *data, uint16_t length, bool complete)) {
    storedHandleSysEx = handle;
    usbMIDI.setHandleSysEx(handleSysEx);
}

void ArduinoHardware::handleSysEx(const uint8_t* data, uint16_t length, bool complete) {
    Serial.println("Received SysEx message with the following bytes:");
    for (unsigned int i = 0; i < length; ++i) {
        Serial.println(data[i], HEX);
    }

    instance->storedHandleSysEx(data, length, complete);
}

void ArduinoHardware::print(std::string s) {
    Serial.println(s.c_str());
}
