#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "CSVColumn.hpp"

namespace csv
{
class CSVReader
{
    public:
    CSVReader();
    CSVReader(const char delimiter, const char quote);
    void set_delimiter(const char delimiter);
    void set_quote(const char quote);
    void set_null_text(const std::string& null_text);
    // returns false if there's an issue opening the file.
    bool open(const std::string& filepath, const bool skip_header = false);
    void close();
    // returns false when reaching end of file
    bool read_line();
    // return the current column's value at idx as type T.
    // if idx is out of range, returns 0 for numeric types for empty string.
    template <typename T>
    T get_column(const std::size_t idx) const;
    // return the current column's value at idx as type T or default to given value on error or NULL.
    // if idx is out of range, returns default value provided.
    template <typename T>
    T get_column_or_default(const std::size_t idx, T default_value) const
    {
        if (this->column_is_null(idx))
            return default_value;

        try
        {
            return this->get_column<T>(idx);
        } catch (const std::exception& e) {
            (void)e;
            return default_value;
        }
    }
    // get column as string and strip quotes (if present.)
    // if idx is out of range, returns empty string.
    std::string get_and_strip_column(const std::size_t idx) const;
    // if idx is out of range, returns true.
    // otherwise, returns true if column is empty or matches set null next.
    bool column_is_null(const std::size_t idx) const;

    private:
    char m_delimiter{};
    char m_quote{};
    std::string m_null_text{};
    std::ifstream m_fstream;
    std::vector<csv::CSVColumn> m_columns;

    void tokenize_line(const std::string& line);
    bool token_is_null(const std::string& token) const;
}; // class CSVReader
}; // namespace csv
