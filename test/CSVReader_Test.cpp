#include "CSVReader.hpp"
#include <assert.h>
#include <math.h>

using namespace csv;

int main()
{
    CSVReader csv;

    csv.open("test.csv", true);
    csv.read_line();

    uint8_t x1 = csv.get_column<uint8_t>(0);
    assert(x1 == 10);

    int8_t x2 = csv.get_column<int8_t>(1);
    assert(x2 == -123);

    float x3 = csv.get_column<float>(2);
    assert(fabsf(x3 - 3.14f) < 0.000001f);

    double x4 = csv.get_column<double>(2);
    assert(abs(x4 - 3.14) < 0.000001);

    double x5 = csv.get_column<double>(3);
    assert(abs(x5 + 3.14) < 0.000001);

    int32_t x6 = csv.get_column<int32_t>(4);
    assert(x6 == 1000000);

    std::string x7 = csv.get_column<std::string>(5);
    assert(x7 == "hello");

    std::string x8 = csv.get_column<std::string>(6);
    assert(x8 == "\"hello\"");

    std::string x9 = csv.get_and_strip_column(6);
    assert(x9 == "hello");

    std::string x10 = csv.get_and_strip_column(7);
    assert(x10 == "hello,there,person");

    std::string x11 = csv.get_column<std::string>(100);
    assert(x11 == "");

    int32_t x12 = csv.get_column<int32_t>(100);
    assert(x12 == 0);

    csv.close();
    return 0;
}