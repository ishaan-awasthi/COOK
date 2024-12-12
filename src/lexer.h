#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

class Lexer
{
public:
    Lexer();
    std::vector<std::string> analyze(std::string line, const std::string &key);
};

#endif