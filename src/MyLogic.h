#ifndef MyLogic_h
#define MyLogic_h

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdint>
typedef uint8_t byte;
#endif

#include <map>
#include "Commands.h"

#include "IHardware.h"

class MyLogic {
public:
    std::map<byte, SysExCommand*> commandRegistry;
    static MyLogic* instance;

    IHardware& hardware;
    MyLogic(IHardware& hardware) : hardware(hardware) {
        instance = this;

        commandRegistry[0x01] = new ReportVersionCommand();
        commandRegistry[0x02] = new GreetingCommand();
    }

    void setup() {
        hardware.setupMIDI();
        hardware.setHandleSysEx(handleSysEx);
    }

    void loop() {
        hardware.sendMIDI(60, 0);
    }

    static SysExCommand* getCommand(byte commandId) {
        if (instance == nullptr) {
            return nullptr;
        }

        if (instance->commandRegistry.find(commandId) != instance->commandRegistry.end()) {
            return instance->commandRegistry[commandId];
        }

        return nullptr;
    }

    static void handleSysEx(const uint8_t* data, uint16_t length, bool complete) {
        if (length < 1) return;

        byte commandId = data[0];

        SysExCommand* command = getCommand(commandId);
        if (command == nullptr) {
            return;
        }

        command->execute(data + 1, length - 1, &(instance->hardware));
    }
};

MyLogic* MyLogic::instance = nullptr;

#endif
