#ifndef IHardware_h
#define IHardware_h

class IHardware {
public:
    virtual void setupMIDI() = 0;
    virtual void sendMIDI(int note, int velocity) = 0;
};

#endif
