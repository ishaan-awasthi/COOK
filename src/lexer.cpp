#include "lexer.h"
#include "utils.h"
#include <iostream>
#include <limits>

Lexer::Lexer() {}

/**
 * Tokenizes a given line of code based on the provided key.
 *
 * @param line: the input string to be tokenized.
 * @param key: the operation or context type to guide tokenization.
 * @return a vector of strings containing the tokens extracted from the line.
 */
std::vector<std::string> Lexer::analyze(std::string line, const std::string &key)
{
    try
    {
        line = toLowerCase(line); // make it lowercase for consistent matching

        if (key == "until")
        {
            // handle reverse while loop logic
            std::string condition;
            int startPos = indexOf(line, "until the");
            if (startPos == -1)
            {
                std::cout << "\n\nError: Double-check your syntax (especially article pointers)!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 10);
            int endDel = findEndDelimiter(sub, 0);
            std::string first = substring(sub, 0, endDel);
            std::string second = "";
            std::string justnum = "false";

            if (contains(line, "is more than"))
            {
                condition = "until more";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                    justnum = "false";
                }
            }
            else if (contains(line, "is less than"))
            {
                condition = "until less";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                    justnum = "false";
                }
            }
            else if (contains(line, "is equal to"))
            {
                condition = "until equal";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                }
            }
            else if (contains(line, "is gone"))
            {
                condition = "until gone";
            }
            else
            {
                condition = "";
            }
            return {condition, first, second, justnum};
        }

        if (key == "conditional")
        {
            // handle conditional tokenization
            std::string condition;
            int startPos = indexOf(line, "the");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax (especially article pointers)!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 4);
            int endDel = findEndDelimiter(sub, 0);
            std::string first = substring(sub, 0, endDel);
            std::string second = "";
            std::string justnum = "false";

            if (contains(line, "is more than"))
            {
                condition = "is more";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                    justnum = "false";
                }
            }
            else if (contains(line, "is less than"))
            {
                condition = "is less";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                    justnum = "false";
                }
            }
            else if (contains(line, "is equal to"))
            {
                condition = "is equal";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                if (matchesRegex(line, ".*\\d.*"))
                {
                    second = std::to_string(std::stoi(removeNonDigits(line)));
                    justnum = "true";
                }
                else
                {
                    int end2 = findEndDelimiter(sub2, 0);
                    second = substring(sub2, 0, end2);
                    justnum = "false";
                }
            }
            else if (contains(line, "is gone"))
            {
                condition = "is gone";
            }
            else if (contains(line, "is same brand as"))
            {
                condition = "string equals";
                std::string sub2 = substring(line, indexOf(line, first) + (int)first.size() + 1);
                sub2 = substring(sub2, indexOf(sub2, "the") + 4);
                int end2 = findEndDelimiter(sub2, 0);
                second = substring(sub2, 0, end2);
            }
            else
            {
                condition = "";
            }
            return {condition, first, second, justnum};
        }

        if (key == "input")
        {
            // handle user input parsing
            std::string sub;
            if (contains(line, "find how much of the"))
            {
                int startPos = indexOf(line, "find how much of the");
                sub = substring(line, startPos + 21);
            }
            else
            {
                int startPos = indexOf(line, "find what brand of the");
                sub = substring(line, startPos + 23);
            }
            int endDel = findEndDelimiter(sub, 0);
            std::string value = substring(sub, 0, endDel);
            return {value};
        }

        if (key == "print")
        {
            // handle print tokenization
            int startPos = indexOf(line, "the");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax (especially article pointers)!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 4);
            std::string value;
            if (contains(line, "\""))
            {
                int quotePos = (int)sub.find("\"");
                if (quotePos == -1)
                {
                    std::cout << "\n\nDouble-check your syntax!\n";
                    return {};
                }
                std::string afterQuote = substring(sub, quotePos + 1);
                int quotePos2 = (int)afterQuote.find("\"");
                if (quotePos2 == -1)
                {
                    std::cout << "\n\nDouble-check your syntax!\n";
                    return {};
                }
                value = substring(afterQuote, 0, quotePos2);
            }
            else
            {
                int endDel = findEndDelimiter(sub, 0);
                value = substring(sub, 0, endDel);
            }
            return {value};
        }

        if (key == "int")
        {
            // handle integer variable tokenization
            int startPos = indexOf(line, "of");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 3);
            int endDel = findEndDelimiter(sub, 0);
            std::string varname = substring(sub, 0, endDel);
            std::string value;
            if (matchesRegex(line, ".*\\d.*"))
            {
                value = std::to_string(std::stoi(removeNonDigits(line)));
            }
            else
            {
                value = "0";
            }
            return {varname, value};
        }

        if (key == "String")
        {
            // handle string variable tokenization
            int startPos = indexOf(line, "brand");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 6);
            int endDel = findEndDelimiter(sub, 0);
            std::string varname = substring(sub, 0, endDel);

            int quotePos = (int)line.find("\"");
            int lastQuotePos = (int)line.rfind("\"");
            if (quotePos == -1 || lastQuotePos == -1 || lastQuotePos == quotePos)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string value = substring(line, quotePos + 1, lastQuotePos);
            return {varname, value};
        }

        if (key == "add" || key == "subtract")
        {
            // handle addition or subtraction tokenization
            int startPos = indexOf(line, "in the");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 7);
            int endDel = findEndDelimiter(sub, 0);
            std::string populate = substring(sub, 0, endDel);

            std::string sub2 = substring(line, indexOf(line, populate) + (int)populate.size() + 1);
            sub2 = substring(sub2, indexOf(sub2, "the") + 4);
            int endDel2 = findEndDelimiter(sub2, 0);
            std::string first = substring(sub2, 0, endDel2);

            std::string sub3 = substring(line, indexOf(line, populate) + (int)populate.size() + 1);
            sub3 = substring(sub3, indexOf(sub3, first) + (int)first.size() + 1);
            sub3 = substring(sub3, indexOf(sub3, "the") + 4);

            std::string second;
            std::string justnum = "false";
            if (matchesRegex(line, ".*\\d.*"))
            {
                second = std::to_string(std::stoi(removeNonDigits(line)));
                justnum = "true";
            }
            else
            {
                int endDel3 = findEndDelimiter(sub3, 0);
                second = substring(sub3, 0, endDel3);
            }
            return {populate, first, second, justnum};
        }

        if (key == "multiply" || key == "divide")
        {
            // handle multiplication or division tokenization
            int startPos = indexOf(line, "in the");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 7);
            int endDel = findEndDelimiter(sub, 0);
            std::string populate = substring(sub, 0, endDel);

            std::string sub2 = substring(line, indexOf(line, sub));
            sub2 = substring(sub2, indexOf(sub2, "the") + 4);
            int endDel2 = findEndDelimiter(sub2, 0);
            std::string first = substring(sub2, 0, endDel2);

            int startPos2 = indexOf(line, "into the");
            if (startPos2 == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub3 = substring(line, startPos2 + 9);

            std::string second;
            std::string justnum = "false";
            if (matchesRegex(line, ".*\\d.*"))
            {
                second = std::to_string(std::stoi(removeNonDigits(line)));
                justnum = "true";
            }
            else
            {
                int endDel3 = findEndDelimiter(sub3, 0);
                second = substring(sub3, 0, endDel3);
                justnum = "false";
            }
            return {populate, first, second, justnum};
        }

        if (key == "mod")
        {
            // handle modulo tokenization
            int startPos = indexOf(line, "in the");
            if (startPos == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub = substring(line, startPos + 7);
            int endDel = findEndDelimiter(sub, 0);
            std::string populate = substring(sub, 0, endDel);

            std::string sub2 = substring(line, indexOf(line, sub));
            sub2 = substring(sub2, indexOf(sub2, "excess") + 7);
            int endDel2 = findEndDelimiter(sub2, 0);
            std::string first = substring(sub2, 0, endDel2);

            int startPos2 = indexOf(line, "into the");
            if (startPos2 == -1)
            {
                std::cout << "\n\nDouble-check your syntax!\n";
                return {};
            }
            std::string sub3 = substring(line, startPos2 + 9);

            std::string second;
            std::string justnum = "false";
            if (matchesRegex(line, ".*\\d.*"))
            {
                second = std::to_string(std::stoi(removeNonDigits(line)));
                justnum = "true";
            }
            else
            {
                int endDel3 = findEndDelimiter(sub3, 0);
                second = substring(sub3, 0, endDel3);
                justnum = "false";
            }
            return {populate, first, second, justnum};
        }

        return {};
    }
    catch (...)
    {
        std::cout << "\n\nError: Unknown exception occurred during tokenization.\n";
        return {};
    }
}
