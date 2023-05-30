[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/alexandswap)
# serial-data-stream

serial-data-stream is a logging package designed for logging time-critical data and dumping it all at once over a serial connection. It provides a templated implementation of a data stream object, allowing you to log various types of data. The intended use case for this package is to log high frequency data, without incurring I/O costs which may affect the quality of the data or the behavior of software running on the microcontroller. The included python script can also be used to automatically read in data from the serial port and save it to a npz file.


## Features

- Templated `DataStream`: The core of the package is the `DataStream` object, which can store the data of any type. Data is logged in memory until it is dumped over serial.
- Python package to parse data from serial and save it to npz files.
- Support for logging multiple data streams in parallel.

## Getting Started

To use the serial-data-stream package in your PlatformIO project, follow these steps:

1. Add this repo to your lid_deps in your `platformio.ini` file:

   ```ini
   lib_deps =
       https://github.com/Roam-Studios/serial-data-stream
   ```

2. Include the serial_data_stream.h file in your code:

   ```cpp
   #include "serial_data_stream.h"
   ```

3. Create an instance of the `DataStream` class with the desired data type and size:

   ```cpp
   // Example: Create a data stream for logging integer values with a size of 100
   DataStream::DataStream<int> my_data_stream("my_stream", 100);
   ```

4. Add data points to the stream using the `add_data_point` method:

   ```cpp
   // Example: Add a new integer data point to the stream
   int dataPoint = 42;
   my_data_stream.add_data_point(dataPoint);
   ```

5. Output the data stream to a serial port:

   ```cpp
   // Example: Output the data stream to serial with a postfix
   const char* postfix = "postfix";
   my_data_stream.output_data_stream(postfix);
   ```
6. Finally, close the data logging session. This will indicate to the python scrip to write all data to file:

   ```cpp
   // Example: Output the data stream to serial with a postfix
   const char* postfix = "postfix";
   Datastream::close("data_file_name");
    ```

7. Upload your code to your Arduino board and open the serial monitor to view the data.
8. To write data to an npz file, run `read_data_stream.py`, which will write the data to a file named `data_file_name.npz` in the current directory, the key for the data will be `my_stream`.

## Example

Here's an example demonstrating the usage of the serial-data-stream package:

```cpp
#include "serial_data_stream.h"

void setup()
{
  // Initialize serial connection before using the data stream
  Serial.begin(115200);

  // Create a data stream for logging integer values with a size of 100
  DataStream::DataStream<int> my_data_stream("my_stream", 100);

  // Add data points to the stream until it is full
  int data_point = 0;
  while (my_data_stream.add_data_point(data_point))
  {
    data_point++;
  }

  // Output the data stream to serial with a postfix
  Serial.println("Data full");
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
```


## Methods
### `close(const char* fname)`

Indicates the termination of data logging to the serial reading script.

- Parameters:
  - `fname`: The name of the file to write data to.

### `DataStream(const char* name, int num_data_points)`

Constructs a new data stream object with the specified name and size.

- Parameters:
  - `name`: The name of the data stream.
  - `num_data_points`: The number of data points the stream can hold.

### `DataStream(const DataStream<T>& other)`

Copy constructor for a data stream object.

- Parameters:
  - `other`: The data stream object to copy from.

### `~DataStream()`

Destructor for a data stream object.

### `DataStream<T>& operator=(const DataStream<T>& other)`

Assignment operator for a data stream object.

- Parameters:
  - `other`: The data stream object to assign from.
- Returns: The updated data stream object.

### `const char* get_name()`

Returns the name of the data stream.

- Returns: The name of the data stream.

### `int get_num_data_points()`

Returns the number of data points that have been added to the data stream.

- Returns: The number of data points in the data stream.

### `int get_size()`

Returns the number of data points the stream can hold.

- Returns: The number of data points the stream can hold.

### `const T* get_data()`

Returns a pointer to the data array.

- Returns: A pointer to the data array.

### `bool add_data_point(T data_point)`

Adds a new data point to the data stream. Will not add data if the stream is full.

- Parameters:
  - `data_point`: The data point to add.
- Returns: True if the data point was added successfully, false if the stream is full.

### `void reset()`

Resets the data stream, deleting all existing data. Implementation simply changes the counter, does not actually delete the data.

### `void output_data_stream(const char* postfix)`

Outputs the data stream to a serial port. The data will be sent with the name "get_name() + postfix".

- Parameters:
  - `postfix`: The postfix to append to the stream name.

These methods provide functionality to work with the `DataStream` class, allowing you to create, manipulate, and output data streams. Refer to the method descriptions for details on their usage and parameters.

## License

This package is open source and distributed under the [MIT License](LICENSE).

## Contributing

Contributions to the serial-data-stream package are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

---

*Docs written with help from ChatGPT*