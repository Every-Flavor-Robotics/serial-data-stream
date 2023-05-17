// Tests for serial_data_stream

#include <Arduino.h>
#include <unity.h>

#include "serial_data_stream.h"

DataStream<int>* data_stream_int;
DataStream<float>* data_stream_float;

void setUp()
{
  data_stream_int = new DataStream<int>("test", 10);
  data_stream_float = new DataStream<float>("test_float", 11);
}

void tearDown()
{
  delete data_stream_int;
  delete data_stream_float;
}

void constructor_tests()
{
  // Test constructor for int
  TEST_ASSERT_EQUAL_STRING("test", data_stream_int->get_name());
  TEST_ASSERT_EQUAL(10, data_stream_int->get_size());
  TEST_ASSERT_EQUAL(0, data_stream_int->get_num_data_points());

  // Test constructor for float
  TEST_ASSERT_EQUAL_STRING("test_float", data_stream_float->get_name());
  TEST_ASSERT_EQUAL(11, data_stream_float->get_size());
  TEST_ASSERT_EQUAL(0, data_stream_float->get_num_data_points());
}

void assignment_operator_tests()
{
  // Test assignment operator for int
  DataStream<int> data_stream_int_2 = *data_stream_int;
  TEST_ASSERT_EQUAL_STRING("test", data_stream_int_2.get_name());
  TEST_ASSERT_EQUAL(10, data_stream_int_2.get_size());
  TEST_ASSERT_EQUAL(0, data_stream_int_2.get_num_data_points());

  // Test assignment operator for float
  DataStream<float> data_stream_float_2 = *data_stream_float;
  TEST_ASSERT_EQUAL_STRING("test_float", data_stream_float_2.get_name());
  TEST_ASSERT_EQUAL(11, data_stream_float_2.get_size());
  TEST_ASSERT_EQUAL(0, data_stream_float_2.get_num_data_points());
}

void copy_constructor_tests()
{
  // Test copy constructor for int
  DataStream<int> data_stream_int_2(*data_stream_int);
  TEST_ASSERT_EQUAL_STRING("test", data_stream_int_2.get_name());
  TEST_ASSERT_EQUAL(10, data_stream_int_2.get_size());
  TEST_ASSERT_EQUAL(0, data_stream_int_2.get_num_data_points());

  // Test copy constructor for float
  DataStream<float> data_stream_float_2(*data_stream_float);
  TEST_ASSERT_EQUAL_STRING("test_float", data_stream_float_2.get_name());
  TEST_ASSERT_EQUAL(11, data_stream_float_2.get_size());
  TEST_ASSERT_EQUAL(0, data_stream_float_2.get_num_data_points());
}

void add_data_point_tests()
{
  // Test add_data_point for int
  data_stream_int->add_data_point(1);
  TEST_ASSERT_EQUAL(1, data_stream_int->get_num_data_points());
  // Retrieve pointer to data
  const int* data = data_stream_int->get_data();
  // Confirm that data is is 1
  TEST_ASSERT_EQUAL(1, data[0]);

  // Test add_data_point for float
  data_stream_float->add_data_point(1.1);
  TEST_ASSERT_EQUAL(1, data_stream_float->get_num_data_points());
  // Retrieve pointer to data
  const float* data_float = data_stream_float->get_data();
  // Confirm that data is is 1.1
  TEST_ASSERT_EQUAL(1.1, data_float[0]);
}

void fill_array_tests()
{
  // Tests to ensure that the array is filled correctly
  // The array should add values until it is full, then it should
  // return false and not add new values
  // Test fill_array for int

  for (int i = 0; i < 10; i++)
  {
    TEST_ASSERT_TRUE(data_stream_int->add_data_point(i));
  }
  // Add additional value
  TEST_ASSERT_FALSE(data_stream_int->add_data_point(10));

  // Check that the last value is 9
  const int* data = data_stream_int->get_data();
  TEST_ASSERT_EQUAL(9, data[9]);

  // Repeat for float
  for (int i = 0; i < 11; i++)
  {
    TEST_ASSERT_TRUE(data_stream_float->add_data_point(i));
  }
  // Add additional value
  TEST_ASSERT_FALSE(data_stream_float->add_data_point(10));

  // Check that the last value is 10
  const float* data_float = data_stream_float->get_data();
  TEST_ASSERT_EQUAL(10, data_float[10]);
}

void output_tests()
{
  // TODO: Figure out how to validate that serial output is correct
  // For now, just check that the function doesn't crash
  data_stream_int->output_data_stream("test");
  data_stream_float->output_data_stream("test");
}

void reset_tests()
{
  // Add some data and then reset
  // Check that num_data_points is 0

  // Test reset for int
  data_stream_int->add_data_point(1);
  // reset
  data_stream_int->reset();
  TEST_ASSERT_EQUAL(0, data_stream_int->get_num_data_points());

  // Repeat for float
  data_stream_float->add_data_point(1.1);
  // reset
  data_stream_float->reset();
  TEST_ASSERT_EQUAL(0, data_stream_float->get_num_data_points());
}

void setup()
{
  delay(2000);  // service delay
  UNITY_BEGIN();
  RUN_TEST(constructor_tests);
  RUN_TEST(assignment_operator_tests);
  RUN_TEST(copy_constructor_tests);
  RUN_TEST(add_data_point_tests);
  RUN_TEST(fill_array_tests);
  RUN_TEST(output_tests);
  RUN_TEST(reset_tests);

  UNITY_END();
}

void loop() {}