# CSV Reader
This is an incredibly simplistic CSV reader to easily read and fetch data from CSV files.

## Building
### Standalone
1. Clone this repo: `git clone git@github.com:Kiyoshika/csv-reader.git`
2. `mkdir build && cd build`
3. `cmake ..`
   * Add `-DDEBUG_MODE=ON` to compile in debug mode
   * Add `-DBUILD_TESTS=ON` to build tests
4. `make` to build the static library `libcsvreader.a`
5. (optional) `make test` to run tests if you decided to build them
### Including in Another CMake Project
1. Add this repo as a submodule to your project
   * E.g., `mkdir ext && cd ext`
   * `git submodule add git@github.com:Kiyoshika/csv-reader.git`
2. In your root `CMakeLists.txt`:
   * `add_subdirectory(ext/csv-reader)`
   * `target_link_libraries([your target] csvreader)`
   * `target_include_directories([your target] PUBLIC ${CMAKE_SOURCE_DIR}/ext/csv-reader/include)`

Where `[your target]` is your executable or library that needs this as a dependency.

By default, this will compile the library in release mode.

## Usage

When calling the constructor, you can pass a custom (single-char) delimiter and (single-char) quote character. By default, these are `,` and `"` respectively.
```cpp
CSVReader csv; // by default using ',' and '"'
CSVReader csv2('|', '\''); // use '|' as delim and single quote as quote char
```

When you `open()` a file, you can choose whether or not to skip the header line. By default, this is true. Every `open()` must have an opposite `close()`. This is not included in the destructor since nothing is opened upon construction and is thus the programmer's responsibility.
```cpp
csv.open("path_to_file.csv"); // by default, skip_header = true
csv.open("path_to_file.csv", false); // read header when calling read_line() next
```
You `read_line()` to read the next line in the CSV file which is internally tokenize. This returns `true` when data has been read and `false` otherwise (e.g., at the end of the file)
```cpp
csv.read_line(); // can be used on-demand

// or, in a while loop
while (csv.read_line()) { ... }
```

You can then use either `get_column<T>(index)` to retrieve and cast the column value to your desired types or use `get_and_strip_column(index)` to read the column as a string and strip the quotes off the end.

All major numeric types are supported as well as `std::string`.

If colum index is out of range, either 0 or empty string is returned depending on the type given.

If a delimiter is present inbetween quotes, it is ignored and read as part of the string. E.g., `"quote,with,delim"` if the delimiter is `,` and quote is `"`.

For reading strings, `get_and_strip_column(index)` is the recommended method to prevent unexpected quotes showing up unless you are certain in the quality of your data.

Below is a full example showcasing some of the usage.
```cpp
#include "CSVReader.hpp"

int main()
{
   CSVReader csv;
   
   csv.open("path_to_file.csv");
   
   while (csv.read_line())
   {
      auto col1 = csv.get_column<uint16_t>(0);
      auto col2 = csv.get_column<double>(1);
      auto col3 = csv.get_column<std::string>(2);
      auto col4 = csv.get_and_strip_column(3); // e.g., "value" -> value
   }
   
   csv.close();
   
   return 0;
}
```