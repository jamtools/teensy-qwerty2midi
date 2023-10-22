#include <unity.h>
#include "MyLogic.h"
#include "MockHardware.h"

void setUp() {
    // This function is called before each test function.
    // You can perform any setup needed here.
}

void tearDown() {
    // This function is called after each test function.
    // You can perform any cleanup needed here.
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
    int expectedVelocity = 127;

    logic.loop();

    TEST_ASSERT_EQUAL_MESSAGE(1, mockHardware.sendMIDICalls.size(), "sendMIDI calls");
    TEST_ASSERT_EQUAL_STRING("sendMIDI", mockHardware.sendMIDICalls[0].first.c_str());
    TEST_ASSERT_EQUAL_INT(expectedNote, mockHardware.sendMIDICalls[0].second.first);
    TEST_ASSERT_EQUAL_INT(expectedVelocity, mockHardware.sendMIDICalls[0].second.second);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_setupMIDI);
    RUN_TEST(test_sendMIDI);

    UNITY_END();
}
