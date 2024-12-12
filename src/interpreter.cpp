#include "interpreter.h"
#include "classifier.h"
#include "lexer.h"
#include "utils.h"
#include <iostream>
#include <limits>

Interpreter::Interpreter() {}

/**
 * Executes a single line of code based on the provided key and tokens.
 *
 * @param key: the keyword representing the operation to perform.
 * @param tokens: the parsed tokens associated with the line.
 * @param variables: a map of variable names to their values.
 * @param inputScanner: the input stream for user input.
 * @param classifier: the classifier for determining line types.
 * @param lexer: the lexer for analyzing lines.
 * @param interpreter: the interpreter itself, for recursive calls.
 */
void Interpreter::execute(const std::string &key, const std::vector<std::string> &tokens,
                          std::map<std::string, VariableValue> &variables,
                          std::istream &inputScanner,
                          Classifier &classifier,
                          Lexer &lexer,
                          Interpreter &interpreter)
{
    // lambda to get the next line from the input stream
    auto getNextLine = [&]() -> std::string
    {
        std::string line;
        if (std::getline(inputScanner, line))
        {
            return line;
        }
        return ""; // return empty string if there are no more lines
    };

    try
    {
        if (key == "until")
        {
            // handle reverse while loop logic
            bool condition = true;
            int second = 0;
            bool isGoneCheck = (tokens[0] == "until gone");
            if (!isGoneCheck)
            {
                if (tokens[3] == "true")
                {
                    second = std::stoi(tokens[2]);
                }
                else
                {
                    if (variables.find(tokens[2]) == variables.end())
                    {
                        std::cout << "\n\nError: Variable not found.\n";
                        return;
                    }
                    if (!variables[tokens[2]].isInt)
                    {
                        std::cout << "\n\nError: Not a valid comparison!\n";
                        return;
                    }
                    second = variables[tokens[2]].intValue;
                }
            }

            // determine the type of condition to check
            if (tokens[0] == "until more")
            {
                if (variables.find(tokens[1]) == variables.end())
                {
                    std::cout << "\n\nError: Variable not found.\n";
                    return;
                }
                condition = (variables[tokens[1]].intValue > second);
            }
            else if (tokens[0] == "until less")
            {
                condition = (variables[tokens[1]].intValue < second);
            }
            else if (tokens[0] == "until equal")
            {
                condition = (variables[tokens[1]].intValue == second);
            }
            else if (tokens[0] == "until gone")
            {
                condition = (variables[tokens[1]].intValue > 0);
            }
            else
            {
                std::cout << "\n\nError: Not a valid comparison!\n";
                return;
            }

            std::string nextline = getNextLine();
            while (!condition && !nextline.empty())
            {
                // classify and execute the next line
                std::string metakey = classifier.classify(nextline);
                std::vector<std::string> metatokens = lexer.analyze(nextline, metakey);
                interpreter.execute(metakey, metatokens, variables, (std::istream &)inputScanner, classifier, lexer, interpreter);

                // re-evaluate the condition after execution
                if (tokens[0] == "until more")
                {
                    condition = (variables[tokens[1]].intValue > second);
                }
                else if (tokens[0] == "until less")
                {
                    condition = (variables[tokens[1]].intValue < second);
                }
                else if (tokens[0] == "until equal")
                {
                    condition = (variables[tokens[1]].intValue == second);
                }
                else if (tokens[0] == "until gone")
                {
                    condition = (variables[tokens[1]].intValue > 0);
                }
                else
                {
                    std::cout << "\n\nError: Not a valid comparison!\n";
                    return;
                }

                if (!condition)
                {
                    nextline = getNextLine();
                }
            }
        }

        if (key == "conditional")
        {
            // handle conditional logic
            bool condition = false;
            int second = 0;
            if (tokens[3] == "true")
            {
                second = std::stoi(tokens[2]);
            }
            else
            {
                if (variables.find(tokens[2]) == variables.end())
                {
                    std::cout << "\n\nError: Variable not found.\n";
                    return;
                }
                if (!variables[tokens[2]].isInt)
                {
                    std::cout << "\n\nError: Not a valid comparison!\n";
                    return;
                }
                second = variables[tokens[2]].intValue;
            }

            // determine the condition type
            if (tokens[0] == "is more")
            {
                condition = (variables[tokens[1]].intValue > second);
            }
            else if (tokens[0] == "is less")
            {
                condition = (variables[tokens[1]].intValue < second);
            }
            else if (tokens[0] == "is equal")
            {
                condition = (variables[tokens[1]].intValue == second);
            }
            else if (tokens[0] == "is gone")
            {
                condition = (variables[tokens[1]].intValue > 0);
            }
            else if (tokens[0] == "string equals")
            {
                if (!variables[tokens[1]].isInt)
                {
                    condition = (variables[tokens[1]].strValue == tokens[2]);
                }
                else
                {
                    condition = false;
                }
            }
            else
            {
                std::cout << "\n\nError: Not a valid comparison!\n";
                return;
            }

            std::string nextline = getNextLine();
            if (condition && !nextline.empty())
            {
                std::string metakey = classifier.classify(nextline);
                std::vector<std::string> metatokens = lexer.analyze(nextline, metakey);
                interpreter.execute(metakey, metatokens, variables, (std::istream &)inputScanner, classifier, lexer, interpreter);
            }
        }

        if (key == "input")
        {
            // prompt for user input
            if (variables.find(tokens[0]) == variables.end())
            {
                std::cout << "\n\nError: Either the variable \"" << tokens[0] << "\" hasn't been initialized, or wrong data type.\n";
                return;
            }
            if (variables[tokens[0]].isInt)
            {
                std::cout << "Input " << tokens[0] << " amount." << std::endl;
                int val;
                std::cin >> val;
                variables[tokens[0]].intValue = val;
            }
            else
            {
                std::cout << "Input " << tokens[0] << " brand." << std::endl;
                std::string val;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, val);
                variables[tokens[0]].strValue = val;
            }
        }

        if (key == "print")
        {
            // print the value of a variable
            std::string varName = tokens[0];
            if (variables.find(varName) != variables.end())
            {
                if (variables[varName].isInt)
                {
                    std::cout << variables[varName].intValue << std::endl;
                }
                else
                {
                    std::cout << variables[varName].strValue << std::endl;
                }
            }
            else
            {
                std::cout << varName << std::endl;
            }
        }

        if (key == "int")
        {
            // declare an integer variable
            VariableValue v;
            v.isInt = true;
            v.intValue = std::stoi(tokens[1]);
            variables[tokens[0]] = v;
        }

        if (key == "String")
        {
            // declare a string variable
            VariableValue v;
            v.isInt = false;
            v.strValue = tokens[1];
            variables[tokens[0]] = v;
        }

        if (key == "add")
        {
            // perform addition
            int first = variables[tokens[1]].intValue;
            int second = (tokens[3] == "true") ? std::stoi(tokens[2]) : variables[tokens[2]].intValue;
            variables[tokens[0]].isInt = true;
            variables[tokens[0]].intValue = first + second;
        }

        if (key == "subtract")
        {
            // perform subtraction
            int first = variables[tokens[1]].intValue;
            int second = (tokens[3] == "true") ? std::stoi(tokens[2]) : variables[tokens[2]].intValue;
            variables[tokens[0]].isInt = true;
            variables[tokens[0]].intValue = first - second;
        }

        if (key == "multiply")
        {
            // perform multiplication
            int first = variables[tokens[1]].intValue;
            int second = (tokens[3] == "true") ? std::stoi(tokens[2]) : variables[tokens[2]].intValue;
            variables[tokens[0]].isInt = true;
            variables[tokens[0]].intValue = first * second;
        }

        if (key == "divide")
        {
            // perform division
            int first = variables[tokens[1]].intValue;
            int second = (tokens[3] == "true") ? std::stoi(tokens[2]) : variables[tokens[2]].intValue;
            if (second == 0)
            {
                std::cout << "\n\nError: Arithmetic exception occurred during calculation!\nDivision by zero.\n";
                return;
            }
            variables[tokens[0]].isInt = true;
            variables[tokens[0]].intValue = first / second;
        }

        if (key == "mod")
        {
            // perform modulo operation
            int first = variables[tokens[1]].intValue;
            int second = (tokens[3] == "true") ? std::stoi(tokens[2]) : variables[tokens[2]].intValue;
            if (second == 0)
            {
                std::cout << "\n\nError: Arithmetic exception!\n";
                return;
            }
            variables[tokens[0]].isInt = true;
            variables[tokens[0]].intValue = first % second;
        }
    }
    catch (...)
    {
        std::cout << "\n\nError: Unknown exception occurred during execution.\n";
    }
}
