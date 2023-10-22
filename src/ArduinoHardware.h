#ifndef ArduinoHardware_h
#define ArduinoHardware_h

#include <string>
#include <Arduino.h>
#include "IHardware.h"

class ArduinoHardware : public IHardware {
public:
    ArduinoHardware();

    void setupMIDI() override;
    void sendMIDI(int note, int velocity) override;
    void sendSysEx(int length, const byte* data);
    void setHandleSysEx(void (*handle)(const uint8_t *data, uint16_t length, bool complete));
    static void handleSysEx(const uint8_t* data, uint16_t length, bool complete);
    void print(std::string s);

private:
    usb_midi_class usbMIDI;
    void (*storedHandleSysEx)(const uint8_t *data, uint16_t length, bool complete);
    static ArduinoHardware* instance;
};

#endif
