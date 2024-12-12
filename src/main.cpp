#include <iostream>
#include <fstream>
#include <map>
#include "variable_value.h"
#include "classifier.h"
#include "lexer.h"
#include "interpreter.h"

int main()
{
    // Open the file using ifstream in the way Hoffman taught us in class
    std::ifstream data_file("./samples/sample.txt");

    // Check if the file was opened successfully
    if (!data_file.is_open())
    {
        std::cout << "Error: Cannot open file ./samples/sample.txt" << std::endl;
        return 1; // Exit with an error code if the file cannot be opened
    }

    // Initialize the main components of the COOK language processing system
    Classifier classifier;
    Lexer lexer;
    Interpreter interpreter;
    std::map<std::string, VariableValue> variables; // To hold variable values during execution

    std::string current_line;

    // Read the file line by line
    while (std::getline(data_file, current_line))
    {
        // Skip empty lines to avoid unnecessary processing
        if (current_line.empty())
            continue;

        // Determine the type of the line using the classifier
        std::string key = classifier.classify(current_line);

        // Break the line into tokens for further processing
        std::vector<std::string> tokens = lexer.analyze(current_line, key);

        // Execute the logic associated with the classified key
        interpreter.execute(key, tokens, variables, data_file, classifier, lexer, interpreter);
    }

    // Close the file explicitly as a good practice
    data_file.close();

    return 0; // Indicate successful program termination
}
