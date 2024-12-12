#include "classifier.h"
#include "utils.h"

Classifier::Classifier() {}

/**
 * classifies the line based on keywords and maps them to COOK's operations.
 *
 * @param line a single line of text from a COOK program
 * @return a string representing the classification of the line, such as "conditional" or "comment"
 */
std::string Classifier::classify(std::string line)
{
    // makes everything lowercase so matching works no matter how the user wrote it
    line = toLowerCase(line);

    // check for keywords and decide what kind of thing the line is doing
    if (contains(line, "until"))
        return "until"; // loop stuff

    if (contains(line, "if"))
        return "conditional"; // checks a condition

    if (contains(line, "find how much of the"))
        return "input"; // asks for a number from the user

    if (contains(line, "find what brand of the"))
        return "input"; // asks for a string from the user

    if (contains(line, "serve"))
        return "print"; // outputs something to the terminal

    if (contains(line, "measure"))
        return "int"; // declares a number variable

    if (contains(line, "prepare"))
        return "String"; // declares a string variable

    if (contains(line, "mix"))
        return "add"; // addition

    if (contains(line, "reduce"))
        return "subtract"; // subtraction

    if (contains(line, "fold"))
        return "multiply"; // multiplication

    if (contains(line, "divide"))
        return "divide"; // division

    if (contains(line, "excess"))
        return "mod"; // modulo (remainder stuff)

    return "comment"; // if it doesn't match anything, it's just a comment
}
