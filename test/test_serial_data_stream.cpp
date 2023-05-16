// Tests for serial_data_stream

#include <Arduino.h>
#include <unity.h>

#include "serial_data_stream.h"

// DataStream<int> data_stream_int("test", 10);
DataStream<float> data_stream_float("test", 10);

void setUp() {}

void tearDown() {}

void constructor_tests()
{
  // Test constructor
  DataStream<float> data_stream_int("test", 10);
  TEST_ASSERT_EQUAL_STRING("test", data_stream_int.get_name());
  TEST_ASSERT_EQUAL(10, data_stream_int.get_size());
  TEST_ASSERT_EQUAL(0, data_stream_int.get_num_data_points());
}

void setup()
{
  delay(2000);  // service delay
  UNITY_BEGIN();
  RUN_TEST(constructor_tests);
  UNITY_END();
}

void loop() {}