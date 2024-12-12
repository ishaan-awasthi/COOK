#include "utils.h"
#include <regex>

/**
 * Checks if the given string matches the provided regex pattern.
 *
 * @param line: the input string to be checked.
 * @param pattern: the regex pattern to match against.
 * @return true if the string matches the pattern, false otherwise.
 */
bool matchesRegex(const std::string &line, const std::string &pattern)
{
    std::regex r(pattern);
    return std::regex_match(line, r);
}

/**
 * Removes all non-digit characters from the input string.
 *
 * @param input: the string to process.
 * @return a string containing only the digit characters from the input.
 */
std::string removeNonDigits(const std::string &input)
{
    std::string result;
    for (char c : input)
    {
        if (c >= '0' && c <= '9')
        {
            result.push_back(c);
        }
    }
    return result;
}

/**
 * Converts a string to lowercase.
 *
 * @param s: the input string to convert.
 * @return a new string where all characters are in lowercase.
 */
std::string toLowerCase(const std::string &s)
{
    std::string result = s;
    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = (char)std::tolower((unsigned char)result[i]);
    }
    return result;
}

/**
 * Checks if a string contains a specific substring.
 *
 * @param line: the string to search in.
 * @param sub: the substring to look for.
 * @return true if the substring is found, false otherwise.
 */
bool contains(const std::string &line, const std::string &sub)
{
    return line.find(sub) != std::string::npos;
}

/**
 * Extracts a substring from the input string based on start and end indices.
 *
 * @param str: the string to extract from.
 * @param start: the starting index.
 * @param end: the ending index (-1 for till the end of the string).
 * @return the extracted substring, or an empty string if indices are invalid.
 */
std::string substring(const std::string &str, int start, int end)
{
    if (end == -1)
    {
        if (start >= 0 && (size_t)start < str.size())
            return str.substr(start);
        else
            return "";
    }
    else
    {
        if (start >= 0 && end > start && (size_t)end <= str.size())
            return str.substr(start, end - start);
        else
            return "";
    }
}

/**
 * Finds the index of the first occurrence of a substring in a string.
 *
 * @param str: the string to search in.
 * @param sub: the substring to find.
 * @return the index of the first occurrence, or -1 if not found.
 */
int indexOf(const std::string &str, const std::string &sub)
{
    size_t pos = str.find(sub);
    if (pos == std::string::npos)
        return -1;
    return (int)pos;
}

/**
 * Finds the index of the next delimiter (space, period, comma, exclamation mark, or question mark) in a string.
 *
 * @param sub: the string to search in.
 * @param startIndex: the index to start searching from.
 * @return the index of the next delimiter, or the size of the string if no delimiter is found.
 */
int findEndDelimiter(const std::string &sub, int startIndex)
{
    int spaceIndex = -1, periodIndex = -1, commaIndex = -1,
        exclamationIndex = -1, questionIndex = -1;

    size_t pos = sub.find(' ', startIndex);
    if (pos != std::string::npos)
        spaceIndex = (int)pos;

    pos = sub.find('.', startIndex);
    if (pos != std::string::npos)
        periodIndex = (int)pos;

    pos = sub.find(',', startIndex);
    if (pos != std::string::npos)
        commaIndex = (int)pos;

    pos = sub.find('!', startIndex);
    if (pos != std::string::npos)
        exclamationIndex = (int)pos;

    pos = sub.find('?', startIndex);
    if (pos != std::string::npos)
        questionIndex = (int)pos;

    int smallestIndex = (int)sub.size();
    if (spaceIndex != -1 && spaceIndex < smallestIndex)
        smallestIndex = spaceIndex;
    if (periodIndex != -1 && periodIndex < smallestIndex)
        smallestIndex = periodIndex;
    if (commaIndex != -1 && commaIndex < smallestIndex)
        smallestIndex = commaIndex;
    if (exclamationIndex != -1 && exclamationIndex < smallestIndex)
        smallestIndex = exclamationIndex;
    if (questionIndex != -1 && questionIndex < smallestIndex)
        smallestIndex = questionIndex;

    return smallestIndex;
}

/**
 * Trims leading and trailing whitespace from a string.
 *
 * @param str: the string to trim.
 * @return a new string with leading and trailing whitespace removed.
 */
std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
        return ""; // no content
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

/**
 * Replaces all occurrences of a substring in a string with another substring.
 *
 * @param str: the string to process.
 * @param from: the substring to replace.
 * @param to: the substring to replace with.
 * @return a new string with all occurrences of 'from' replaced by 'to'.
 */
std::string replaceAll(const std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return str;

    std::string result = str;
    size_t startPos = 0;
    while ((startPos = result.find(from, startPos)) != std::string::npos)
    {
        result.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return result;
}
