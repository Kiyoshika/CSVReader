#include "CSVColumn.hpp"

using namespace csv;

CSVColumn::CSVColumn(const std::string& value, bool is_null)
{
    this->m_value = value;
    this->m_is_null = is_null;
}

const std::string& CSVColumn::get_value() const
{
    return this->m_value;
}

std::string CSVColumn::get_stripped_value(const char quote) const
{
    const std::string& str = this->get_value();

    if (str.empty())
        return std::string{};

    // if the quote is not present on both sides, return the string as is
    // (although, this is almost surely a cause of another problem)
    if (str[0] != quote && str[str.length() - 1] != quote)
        return str;

    std::string stripped_str;
    for (std::size_t i = 1; i < str.length() - 1; ++i)
        stripped_str.push_back(str[i]);

    return stripped_str;
}

bool CSVColumn::is_null() const
{
    return this->m_is_null;
}

void CSVColumn::set_null(bool is_null)
{
    this->m_is_null = is_null;
}