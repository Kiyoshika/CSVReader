#include "CSVReader.hpp"
#include <assert.h>
#include <math.h>

using namespace csv;

int main()
{
    CSVReader csv;
    csv.set_null_text("NA");

    csv.open("test.csv", true);
    csv.read_line();

    uint8_t x1 = csv.get_column<uint8_t>(0);
    assert(x1 == 10);
    x1 = csv.get_column_or_default<uint8_t>(0, 0);
    assert(x1 == 10);
    assert(!csv.column_is_null(0));

    int8_t x2 = csv.get_column<int8_t>(1);
    assert(x2 == -123);
    x2 = csv.get_column_or_default<int8_t>(1, 0);
    assert(x2 == -123);
    assert(!csv.column_is_null(1));

    float x3 = csv.get_column<float>(2);
    assert(fabsf(x3 - 3.14f) < 0.000001f);
    x3 = csv.get_column_or_default<float>(2, 0.0f);
    assert(fabsf(x3 - 3.14f) < 0.000001f);
    assert(!csv.column_is_null(2));

    double x4 = csv.get_column<double>(2);
    assert(abs(x4 - 3.14) < 0.000001);
    x4 = csv.get_column_or_default<double>(2, 0.0);
    assert(abs(x4 - 3.14) < 0.000001);

    double x5 = csv.get_column<double>(3);
    assert(abs(x5 + 3.14) < 0.000001);
    assert(!csv.column_is_null(3));

    int32_t x6 = csv.get_column<int32_t>(4);
    assert(x6 == 1000000);
    x6 = csv.get_column_or_default<int32_t>(4, 0);
    assert(x6 == 1000000);
    assert(!csv.column_is_null(4));

    std::string x7 = csv.get_column<std::string>(5);
    assert(x7 == "hello");
    x7 = csv.get_column_or_default<std::string>(5, "");
    assert(x7 == "hello");
    // this should fail casting to int, so we check a default value of 10
    auto x7_2 = csv.get_column_or_default<int32_t>(5, 10);
    assert(x7_2 == 10);
    assert(!csv.column_is_null(5));

    std::string x8 = csv.get_column<std::string>(6);
    assert(x8 == "\"hello\"");
    assert(!csv.column_is_null(6));

    std::string x9 = csv.get_and_strip_column(6);
    assert(x9 == "hello");

    std::string x10 = csv.get_and_strip_column(7);
    assert(x10 == "hello,there,person");
    assert(!csv.column_is_null(7));

    assert(csv.column_is_null(8)); // empty column
    assert(csv.column_is_null(9)); // matches null text "NA" set at beginning

    std::string x11 = csv.get_column<std::string>(100);
    assert(x11 == "");
    assert(csv.column_is_null(100));

    int32_t x12 = csv.get_column<int32_t>(100);
    assert(x12 == 0);

    csv.close();
    return 0;
}