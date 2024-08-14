add_library(csvreader STATIC CSVReader.cpp CSVColumn.cpp)
target_link_libraries(csvreader m)
target_include_directories(csvreader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)