// Unit tests for RunningAverage, run on the desktop by
// `pio test -e native`. Same library the board uses.
#include <unity.h>

#include "RunningAverage.h"

void setUp(void) {}
void tearDown(void) {}

void test_empty_average_is_zero(void) {
    RunningAverage avg(4);
    TEST_ASSERT_EQUAL_INT(0, avg.count());
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, avg.average());
}

void test_average_before_window_fills(void) {
    RunningAverage avg(4);
    avg.add(10.0);
    avg.add(20.0);
    TEST_ASSERT_EQUAL_INT(2, avg.count());
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 15.0, avg.average());
}

void test_oldest_reading_leaves_the_window(void) {
    RunningAverage avg(3);
    avg.add(1.0);
    avg.add(2.0);
    avg.add(3.0);
    avg.add(10.0);  // pushes the 1.0 out
    TEST_ASSERT_EQUAL_INT(3, avg.count());
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 5.0, avg.average());
}

void test_clear_starts_over(void) {
    RunningAverage avg(2);
    avg.add(5.0);
    avg.clear();
    TEST_ASSERT_EQUAL_INT(0, avg.count());
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, avg.average());
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_empty_average_is_zero);
    RUN_TEST(test_average_before_window_fills);
    RUN_TEST(test_oldest_reading_leaves_the_window);
    RUN_TEST(test_clear_starts_over);
    return UNITY_END();
}
