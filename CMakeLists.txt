cmake_minimum_required(VERSION 3.8)
project(csvreader)

option(DEBUG_MODE OFF)
option(BUILD_TESTS OFF)

if (${DEBUG_MODE})
    message("COMPILING IN DEBUG MODE...")
    set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Wextra")
else()
    message("COMPILING IN RELEASE MODE...")
    set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if (${BUILD_TESTS})
    message("ENABLED TESTS")
    include(CTest)
    enable_testing()
    add_subdirectory(test)
    configure_file(test/test.csv ${CMAKE_CURRENT_BINARY_DIR}/test/test.csv COPYONLY)
endif()
