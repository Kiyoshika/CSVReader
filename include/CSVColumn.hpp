#pragma once

#include <string>

namespace csv
{
struct CSVColumn
{
    public:
    CSVColumn(const std::string& value, bool is_null);
    const std::string& get_value() const;
    bool is_null() const;
    void set_null(bool is_null);

    private:
    std::string m_value;
    bool m_is_null;
}; // class CSVColumn
}; // namespace csv