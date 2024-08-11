add_executable(CSVReader_Test CSVReader_Test.cpp)
target_link_libraries(CSVReader_Test csvreader)
target_include_directories(CSVReader_Test PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_test(NAME CSVReader_Test COMMAND CSVReader_Test)