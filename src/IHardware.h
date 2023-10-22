#ifndef IHardware_h
#define IHardware_h

class IHardware {
public:
    virtual void setupMIDI() = 0;
    virtual void sendMIDI(int note, int velocity) = 0;
    virtual void sendSysEx(int length, const byte* data) = 0;
    virtual void setHandleSysEx(void (*fptr)(const uint8_t *data, uint16_t length, bool complete)) = 0;
};

#endif
