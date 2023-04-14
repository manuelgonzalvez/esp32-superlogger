#include "unity.h"

// Declare the function to be tested
int addition(int a, int b);

void test_addition(void) {
  // Test case 1
  TEST_ASSERT_EQUAL_INT(5, addition(2, 3));

  // Test case 2
  TEST_ASSERT_EQUAL_INT(-1, addition(2, -3));

  // Add more test cases here as needed
}

int main(void) {
  UNITY_BEGIN();

  // Run the test suite
  RUN_TEST(test_addition);

  return UNITY_END();
}
