#ifndef TESTING_LEXER_H
#define TESTING_LEXER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include "Environment.h"

enum class Lexicon {
    Define,
    Print,
};

class ILexerComponent;

class Lexer {
public:
    Lexer();

    ~Lexer() = default;

    void run(std::ifstream &file);

private:
    std::shared_ptr<ILexerComponent> defineComponent;
    std::shared_ptr<ILexerComponent> printComponent;
    Environment environment;

};

#endif //TESTING_LEXER_H
