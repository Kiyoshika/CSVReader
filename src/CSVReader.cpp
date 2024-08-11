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

void CSVReader::set_quote(const char quote) {
    this->m_quote = quote;
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

void CSVReader::tokenize_line(const std::string& line)
{
    bool inside_quote = false;
    std::string current_token;
    for (const char c : line)
    {
        if (c == this->m_quote)
            inside_quote = !inside_quote;

        if (!inside_quote && c == this->m_delimiter)
        {
            this->m_tokens.push_back(current_token);
            current_token.clear();
            continue;
        }

        current_token.push_back(c);
    }

    if (!current_token.empty())
        this->m_tokens.push_back(current_token);
}

template<>
uint8_t CSVReader::get_column<uint8_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stoul(this->m_tokens[idx]);
}

template<>
uint16_t CSVReader::get_column<uint16_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stoul(this->m_tokens[idx]);
}

template<>
uint32_t CSVReader::get_column<uint32_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stoul(this->m_tokens[idx]);
}

template<>
uint64_t CSVReader::get_column<uint64_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stoull(this->m_tokens[idx]);
}

template<>
int8_t CSVReader::get_column<int8_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stol(this->m_tokens[idx]);
}

template<>
int16_t CSVReader::get_column<int16_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stol(this->m_tokens[idx]);
}

template<>
int32_t CSVReader::get_column<int32_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stol(this->m_tokens[idx]);
}

template<>
int64_t CSVReader::get_column<int64_t>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0;

    return std::stoll(this->m_tokens[idx]);
}

template<>
double CSVReader::get_column<double>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0.0;

    return std::stod(this->m_tokens[idx]);
}

template<>
float CSVReader::get_column<float>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return 0.0f;

    return std::stof(this->m_tokens[idx]);
}

template<>
std::string CSVReader::get_column<std::string>(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return std::string{};

    return this->m_tokens[idx];
}

std::string CSVReader::get_and_strip_column(const std::size_t idx)
{
    if (idx >= this->m_tokens.size())
        return std::string{};

    std::string& str = this->m_tokens[idx];
    if (str.length() < 3)
        return std::string{};

    // if the quote is not present on both sides, return the string as is
    // (although, this is almost surely a cause of another problem)
    if (str[0] != this->m_quote && str[str.length() - 1] != this->m_quote)
        return str;

    std::string stripped_str;
    for (std::size_t i = 1; i < str.length() - 1; ++i)
        stripped_str.push_back(str[i]);

    return stripped_str;
}