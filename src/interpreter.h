#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <map>
#include "variable_value.h"

class Classifier;
class Lexer;

class Interpreter
{
public:
    Interpreter();
    void execute(
        const std::string &key,
        const std::vector<std::string> &tokens,
        std::map<std::string, VariableValue> &variables,
        std::istream &inputScanner,
        Classifier &classifier,
        Lexer &lexer,
        Interpreter &interpreter);
};

#endif