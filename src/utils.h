#ifndef UTILS_H
#define UTILS_H

#include <string>

bool matchesRegex(const std::string &line, const std::string &pattern);
std::string removeNonDigits(const std::string &input);
std::string toLowerCase(const std::string &s);
bool contains(const std::string &line, const std::string &sub);
std::string substring(const std::string &str, int start, int end = -1);
int indexOf(const std::string &str, const std::string &sub);
int findEndDelimiter(const std::string &sub, int startIndex);

#endif