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

bool CSVColumn::is_null() const
{
    return this->m_is_null;
}

void CSVColumn::set_null(bool is_null)
{
    this->m_is_null = is_null;
}