#ifndef TESTING_ENVIRONMENT_H
#define TESTING_ENVIRONMENT_H

#include <string>
#include <stdexcept>
#include "../Sequence.h"

class Environment {
public:
    Sequence &getVariable(const std::string &variableName) {
        try {
            return sequences.at(variableName);
        } catch (std::out_of_range e) {
            throw e;
        }
    }

    void setVariable(const std::string &variableName, Sequence &value) {
        try {
            sequences.insert(std::pair<std::string, Sequence>(variableName, value));
        } catch (std::out_of_range e) {
            throw e;
        }
    }

private:
    std::map<std::string, Sequence> sequences;
};


#endif //TESTING_ENVIRONMENT_H
