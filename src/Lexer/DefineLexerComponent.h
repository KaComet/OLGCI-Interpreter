#ifndef TESTING_DEFINELEXERCOMPONENT_H
#define TESTING_DEFINELEXERCOMPONENT_H

#include "ILexerComponent.h"

#include <memory>

enum class Lexicon_Define {
    Sequence
};

class DefineLexerComponent : public ILexerComponent {
public:
    void run(std::ifstream &file, Environment &environment) override;

private:

    Sequence loadSequence(std::ifstream &inputStream);
};


#endif //TESTING_DEFINELEXERCOMPONENT_H
