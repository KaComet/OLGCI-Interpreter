#ifndef TESTING_PRINTLEXERCOMPONENT_H
#define TESTING_PRINTLEXERCOMPONENT_H

#include "ILexerComponent.h"

#include <memory>

enum class Lexicon_Print {
    K_Maps,
    EXCITATION_TABLE
};

class PrintLexerComponent : public ILexerComponent {
public:
    void run(std::ifstream &file, Environment &environment) override;

private:
    void printSequenceAllK_Maps(std::ifstream &inputStream, Environment &environment);
    void printSequenceExcitation(std::ifstream &inputStream, Environment &environment);

};

#endif //TESTING_PRINTLEXERCOMPONENT_H
