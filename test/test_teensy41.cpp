#include <Unity.h>

void test_addition() {
    // Arrange
    int a = 2;
    int b = 3;

    // Act
    int result = a + b;

    // Assert
    TEST_ASSERT_EQUAL_INT(5, result);
}

void setup() {
    // Setup your test environment here (if needed)
}

void loop() {
    // Not used for tests, you can leave it empty
}

int main() {
    UNITY_BEGIN();

    // Run your test cases here
    RUN_TEST(test_addition);

    UNITY_END();

    return 0;
}
