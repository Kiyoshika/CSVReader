#include "CSVReader.hpp"

using namespace csv;

CSVReader::CSVReader()
{
    this->set_delimiter(',');
    this->set_quote('"');
}

CSVReader::CSVReader(const char delimiter, const char quote)
{
    this->set_delimiter(delimiter);
    this->set_quote(quote);
}

void CSVReader::set_delimiter(const char delimiter)
{
    this->m_delimiter = delimiter;
}

void CSVReader::set_quote(const char quote)
{
    this->m_quote = quote;
}

void CSVReader::set_null_text(const std::string& null_text)
{
    this->m_null_text = null_text;
}

bool CSVReader::open(const std::string& filepath, const bool skip_header)
{
    std::ifstream file(filepath);
    if (!file.is_open())
        return false;

    this->m_fstream = std::move(file);

    std::string line;
    if (skip_header)
        std::getline(this->m_fstream, line);

    return true;
}

void CSVReader::close()
{
    this->m_fstream.close();
}

bool CSVReader::read_line()
{
    std::string line;
    if (std::getline(this->m_fstream, line))
    {
        this->tokenize_line(line);
        return true;
    }

    return false;
}

bool CSVReader::token_is_null(const std::string& token) const
{
    return token.empty() || (!this->m_null_text.empty() && token == this->m_null_text);
}

void CSVReader::tokenize_line(const std::string& line)
{
    this->m_columns.clear();

    bool inside_quote = false;
    std::string current_token;
    for (const char c : line)
    {
        if (c == this->m_quote)
            inside_quote = !inside_quote;

        if (!inside_quote && c == this->m_delimiter)
        {
            this->m_columns.emplace_back(current_token, this->token_is_null(current_token));
            current_token.clear();
            continue;
        }

        current_token.push_back(c);
    }

    if (!current_token.empty())
        this->m_columns.emplace_back(current_token, this->token_is_null(current_token));
}

template<>
uint8_t CSVReader::get_column<uint8_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stoul(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
uint16_t CSVReader::get_column<uint16_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stoul(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
uint32_t CSVReader::get_column<uint32_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stoul(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
uint64_t CSVReader::get_column<uint64_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stoull(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
int8_t CSVReader::get_column<int8_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stol(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
int16_t CSVReader::get_column<int16_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stol(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
int32_t CSVReader::get_column<int32_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stol(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
int64_t CSVReader::get_column<int64_t>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0;

    return std::stoll(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
double CSVReader::get_column<double>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0.0;

    return std::stod(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
float CSVReader::get_column<float>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return 0.0f;

    return std::stof(this->m_columns[idx].get_stripped_value(this->m_quote));
}

template<>
std::string CSVReader::get_column<std::string>(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return std::string{};

    return this->m_columns[idx].get_value();
}

std::string CSVReader::get_and_strip_column(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return std::string{};

    return this->m_columns[idx].get_stripped_value(this->m_quote);
}

bool CSVReader::column_is_null(const std::size_t idx) const
{
    if (idx >= this->m_columns.size())
        return true;

    return this->m_columns[idx].is_null();
}