#ifndef MyLogic_h
#define MyLogic_h

#include "IHardware.h"

class MyLogic {
public:
    IHardware& hardware;
    MyLogic(IHardware& hardware) : hardware(hardware) {}

    void setup() {
        hardware.setupMIDI();
    }

    void loop() {
        // Your MIDI logic goes here, for example:
        hardware.sendMIDI(60, 127);  // Sending a MIDI note
    }
};

#endif
