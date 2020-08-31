#ifndef TESTING_ILEXERCOMPONENT_H
#define TESTING_ILEXERCOMPONENT_H

#include <fstream>
#include <memory>
#include "Lexer.h"

class ILexerComponent  {
public:
    virtual void run(std::ifstream &file, Environment &environment) = 0;
};

#endif //TESTING_ILEXERCOMPONENT_H
