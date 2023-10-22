#ifndef ArduinoHardware_h
#define ArduinoHardware_h

#include <Arduino.h>
#include "IHardware.h"
#include "usb_dev.h"
#include "usb_names.h"
#include "core_pins.h"
#include "HardwareSerial.h"
#include "usb_serial.h"
#include <MIDI.h>  // Include Teensy MIDI library

class ArduinoHardware : public IHardware {
public:
    usb_midi_class usbMIDI;

    void setupMIDI() override {
        // Initialization, if any, can go here
        // Teensy MIDI usually does not require explicit initialization
    }

    void sendMIDI(int note, int velocity) override {
        usbMIDI.sendNoteOn(note, velocity, 1);  // Send NoteOn message on channel 1
    }

    void sendSysEx(int length, const byte* data) {
        usbMIDI.sendSysEx(length, data);
    }

    void setHandleSysEx(void (*handle)(const uint8_t *data, uint16_t length, bool complete)) {
        usbMIDI.setHandleSysEx(handle);
    }
};

#endif
