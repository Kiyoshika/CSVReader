add_library(csvreader STATIC CSVReader.cpp)
target_link_libraries(csvreader m)
target_include_directories(csvreader PUBLIC ${CMAKE_SOURCE_DIR}/include)