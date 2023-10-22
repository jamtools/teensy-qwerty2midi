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

    // Mock the setupMIDI method
    void setupMIDI() {
        setupMIDICalls.push_back({"setupMIDI", {0, 0}});
    }

    // Mock the sendMIDI method
    void sendMIDI(int note, int velocity) {
        sendMIDICalls.push_back({"sendMIDI", {note, velocity}});
    }
};

#endif  // MOCK_HARDWARE_H
