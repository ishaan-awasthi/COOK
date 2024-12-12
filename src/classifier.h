#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>

class Classifier
{
public:
    Classifier();
    std::string classify(std::string line);
};

#endif