
// Templatized implementation of a data stream object

#ifndef DATA_STREAM_H
#define DATA_STREAM_H

#include <Arduino.h>

namespace DataStream
{

/**
 * Indicates the termination of data logging to the serial reading script.
 * @param fname The name of the file to write data to.
 */
void close(const char* fname)
{
  Serial.print("_data_stream_:_close_:");
  Serial.println(fname);
}

// Templatized implementation of data stream
template <typename T>
class DataStream
{
 public:
  /**
   * Constructs a new data stream object with the specified name and size.
   * @param name The name of the data stream.
   * @param num_data_points The number of data points the stream can hold.
   */
  DataStream(const char* name, int num_data_points);

  /**
   * Copy constructor for a data stream object.
   * @param other The data stream object to copy from.
   */
  DataStream(const DataStream<T>& other);

  /**
   * Destructor for a data stream object.
   */
  ~DataStream();

  /**
   * Assignment operator for a data stream object.
   * @param other The data stream object to assign from.
   * @return The updated data stream object.
   */
  DataStream<T>& operator=(const DataStream<T>& other);

  /**
   * Returns the name of the data stream.
   * @return The name of the data stream.
   */
  const char* get_name();

  /**
   * Returns the number of data points that have been added to the data stream.
   * @return The number of data points in the data stream.
   */
  int get_num_data_points();

  /**
   * Returns the number of data points the stream can hold.
   * @return The number of data points the stream can hold.
   */
  int get_size();
  const T* get_data();

  /**
   * Adds a new data point to the data stream. Will not add data if the stream
   * is full.
   * @param data_point The data point to add.
   * @return True if the data point was added successfully, false if the stream
   * is full.
   */
  bool add_data_point(T data_point);

  /**
   * Resets the data stream, deleting all existing data. Implementation simply
   * changes the counter, does not actually delete the data.
   */
  void reset();

  /**
   * Outputs the data stream to a serial port. The data will be the sent with
   * the name "get_name() + postfix".
   * @param postfix The postfix to append to the stream name.
   */
  void output_data_stream(const char* postfix);

 private:
  const char* name;
  int num_data_points;
  T* data;
  int cur_data_point = 0;
};

template <typename T>
DataStream<T>::DataStream(const char* name, int num_data_points)
{
  this->name = name;
  this->num_data_points = num_data_points;
  this->data = new T[num_data_points];
}

template <typename T>
DataStream<T>::~DataStream()
{
  delete[] data;
  data = nullptr;
}

// Assignment operator
template <typename T>
DataStream<T>& DataStream<T>::operator=(const DataStream<T>& other)
{
  if (this != &other)
  {
    this->name = other.name;
    this->num_data_points = other.num_data_points;
    this->data = new T[num_data_points];

    for (int i = 0; i < num_data_points; i++)
    {
      this->data[i] = other.data[i];
    }
  }

  return *this;
}

// Copy constructor
template <typename T>
DataStream<T>::DataStream(const DataStream<T>& other)
{
  this->name = other.name;
  this->num_data_points = other.num_data_points;
  this->data = new T[num_data_points];

  for (int i = 0; i < num_data_points; i++)
  {
    this->data[i] = other.data[i];
  }
}

// Return name of the data stream
template <typename T>
const char* DataStream<T>::get_name()
{
  return name;
}

// Return size of the data stream
template <typename T>
int DataStream<T>::get_size()
{
  return num_data_points;
}

// Return number of data points that have been added to the data stream
template <typename T>
int DataStream<T>::get_num_data_points()
{
  return cur_data_point;
}

// Return pointer to the data
// This could be dangerous (dangling pointer) if the data stream is deleted
// However, this is preferred over returning a copy, which could be expensive
template <typename T>
const T* DataStream<T>::get_data()
{
  return data;
}

// Add a new data point to the data stream
// This could
template <typename T>
bool DataStream<T>::add_data_point(T data_point)
{
  if (cur_data_point < num_data_points)
  {
    // Append data and increment counter
    data[cur_data_point] = data_point;
    cur_data_point++;

    return true;
  }

  return false;
}

template <typename T>
void DataStream<T>::reset()
{
  // Don't need to do anything else, just reset the counter
  cur_data_point = 0;
}

// Templatized function to output a data stream to a serial port
template <typename T>
void DataStream<T>::output_data_stream(const char* postfix)
{
  // Print the name of the data stream
  Serial.print("_data_stream_:");
  Serial.print(get_name());
  Serial.print("_");
  Serial.print(postfix);
  Serial.print(":");

  // Print the data
  for (int i = 0; i < get_num_data_points(); i++)
  {
    Serial.print(data[i], 10);
    Serial.print(",");
  }

  // Print a newline
  Serial.println();
}

}  // namespace DataStream
#endif
