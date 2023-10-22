#ifndef MOCK_HARDWARE_H
#define MOCK_HARDWARE_H

#include <vector>
#include <utility>
#include <string>

class MockHardware : public IHardware {
public:
    // Add member variables to track calls
    std::vector<std::pair<std::string, std::pair<int, int>>> sendMIDICalls;
    std::vector<std::pair<std::string, std::pair<int, int>>> setupMIDICalls;
    std::vector<std::pair<std::string, std::pair<int, const byte*>>> sendSysExCalls;

    void (*storedSysExHandler)(const uint8_t *data, uint16_t length, bool complete);

    // Mock the setupMIDI method
    void setupMIDI() {
        setupMIDICalls.push_back({"setupMIDI", {0, 0}});
    }

    // Mock the sendMIDI method
    void sendMIDI(int note, int velocity) {
        sendMIDICalls.push_back({"sendMIDI", {note, velocity}});
    }

    void sendSysEx(int length, const byte* data) {
        byte* copied_data = new byte[length];
        std::memcpy(copied_data, data, length);

        std::pair<int, const byte*> inner_pair(length, copied_data);
        std::pair<std::string, std::pair<int, const byte*>> outer_pair("sendSysEx", inner_pair);
        sendSysExCalls.push_back(outer_pair);
    }

    void setHandleSysEx(void (*handle)(const uint8_t *data, uint16_t length, bool complete)) {
        storedSysExHandler = handle;
    }

    void print(std::string s) {

    }
};

#endif  // MOCK_HARDWARE_H
