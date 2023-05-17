#include <Arduino.h>

#include "data_stream.h"

void setup()
{
  // Create a data stream for logging integer values with a size of 100
  DataStream::DataStream<int> my_data_stream("my_stream", 100);

  // Add data points to the stream until it is full
  int data_point = 0;
  while (my_data_stream.add_data_point(data_point))
  {
    data_point++;
  }

  // Output the data stream to serial with a postfix
  const char* postfix = "postfix";
  my_data_stream.output_data_stream(postfix);

  // Close the data logging session
  const char* file_name = "data_file_name";
  DataStream::close(file_name);
}

void loop()
{
  // do nothing
}