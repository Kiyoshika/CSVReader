#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace csv
{
class CSVReader
{
    public:
    CSVReader();
    CSVReader(const char delimiter, const char quote);
    void set_delimiter(const char delimiter);
    void set_quote(const char quote);
    // returns false if there's an issue opening the file.
    bool open(const std::string& filepath, const bool skip_header = false);
    void close();
    // returns false when reaching end of file
    bool read_line();
    // return the current column's value at idx as type T.
    // if idx is out of range, returns 0 for numeric types for empty string.
    template <typename T>
    T get_column(const std::size_t idx);
    // get column as string and strip quotes (if present.)
    // if idx is out of range, returns empty string.
    std::string get_and_strip_column(const std::size_t idx);

    private:
    char m_delimiter{};
    char m_quote{};
    std::ifstream m_fstream;
    std::vector<std::string> m_tokens;

    void tokenize_line(const std::string& line);
}; // class CSVReader
}; // namespace csv