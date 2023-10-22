#include <unity.h>
#include "MyLogic.h"
#include "MockHardware.h"

std::string getContentFromSysExMessage(MockHardware* mockHardware, int callNum) {
    int actualLength = mockHardware->sendSysExCalls[callNum].second.first;
    const byte* actualBytes = mockHardware->sendSysExCalls[callNum].second.second;
    std::string convertedString(actualBytes, actualBytes + actualLength);
    return convertedString.substr(3, convertedString.size() - 4);
}

void setUp() {
    // This function is called before each test function.
}

void tearDown() {
    // This function is called after each test function.
}

void test_setupMIDI() {
    MockHardware mockHardware;
    MyLogic logic(mockHardware);

    TEST_MESSAGE("MockHardware::sendMIDI(note=");

    logic.setup();

    TEST_ASSERT_EQUAL_MESSAGE(1, mockHardware.setupMIDICalls.size(), "setupMidi calls");
    TEST_ASSERT_EQUAL_STRING("setupMIDI", mockHardware.setupMIDICalls[0].first.c_str());
}

void test_sendMIDI() {
    MockHardware mockHardware;
    MyLogic logic(mockHardware);
    int expectedNote = 60;
    int expectedVelocity = 0;

    logic.setup();
    logic.loop();

    // TEST_ASSERT_EQUAL_MESSAGE(1, mockHardware.sendMIDICalls.size(), "sendMIDI calls");
    // TEST_ASSERT_EQUAL_STRING("sendMIDI", mockHardware.sendMIDICalls[0].first.c_str());
    // TEST_ASSERT_EQUAL_INT(expectedNote, mockHardware.sendMIDICalls[0].second.first);
    // TEST_ASSERT_EQUAL_INT(expectedVelocity, mockHardware.sendMIDICalls[0].second.second);

    // currently disabled the sending of the message on loop
    TEST_ASSERT_EQUAL_MESSAGE(0, mockHardware.sendMIDICalls.size(), "sendMIDI calls");
}

void test_versionCommand() {
    MockHardware mockHardware;
    MyLogic logic(mockHardware);

    logic.setup();

    const uint8_t commandId = 0x01;
    const uint8_t data_arr[] = {0x00, 0x00, 0x00, 0x00, commandId};
    const uint8_t* data = data_arr;

    mockHardware.storedSysExHandler(data, 5, true);

    TEST_ASSERT_EQUAL_MESSAGE(1, mockHardware.sendSysExCalls.size(), "sendSysEx calls");
    std::string capturedVersion = getContentFromSysExMessage(&mockHardware, 0);
    TEST_ASSERT_EQUAL_STRING("test", capturedVersion.c_str());
}

void test_greetingCommand() {
    MockHardware mockHardware;
    MyLogic logic(mockHardware);

    logic.setup();

    const uint8_t commandId = 0x02;
    const uint8_t data_arr[] = {0x00, 0x00, 0x00, 0x00, commandId};
    const uint8_t* data = data_arr;

    mockHardware.storedSysExHandler(data, 5, true);

    TEST_ASSERT_EQUAL_MESSAGE(1, mockHardware.sendSysExCalls.size(), "sendSysEx calls");
    std::string capturedVersion = getContentFromSysExMessage(&mockHardware, 0);
    TEST_ASSERT_EQUAL_STRING("Hey there bud", capturedVersion.c_str());
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_setupMIDI);
    RUN_TEST(test_sendMIDI);
    RUN_TEST(test_versionCommand);
    RUN_TEST(test_greetingCommand);

    UNITY_END();
}
