#include "DefineLexerComponent.h"

std::pair<std::string, Lexicon_Define> Lexicon_Define_Data[] = {
        std::make_pair("Sequence", Lexicon_Define::Sequence)
};

const std::map<std::string, Lexicon_Define> lexicon_define(Lexicon_Define_Data, Lexicon_Define_Data +
                                                                                sizeof Lexicon_Define_Data /
                                                                                sizeof Lexicon_Define_Data[0]);

void DefineLexerComponent::run(std::ifstream &file, Environment &environment) {
    std::string tmpD;
    file >> tmpD;

    Lexicon_Define thisLexD;
    try {
        thisLexD = lexicon_define.at(tmpD);
    } catch (std::out_of_range &e) {
        std::cout << "Symbol \"" << tmpD << "\" not recognized. Exiting...";
        std::exit(1);
    }

    switch (thisLexD) {
        case Lexicon_Define::Sequence:
            std::string tmpSQ;
            file >> tmpSQ;
            Sequence sequence = loadSequence(file);
            environment.setVariable(tmpSQ, sequence);
            break;
    }
}

Sequence DefineLexerComponent::loadSequence(std::ifstream &inputStream) {
    std::optional<Sequence> result = std::nullopt;
    bool hasFoundEnd = false;
    while (!inputStream.eof()) {
        std::string tmpStr;

        inputStream >> tmpStr;
        unsigned int nBits = std::stoi(tmpStr);

        inputStream >> tmpStr;
        inputStream >> tmpStr;
        inputStream >> tmpStr;
        MinTerm defaultState = std::stoi(tmpStr);

        result = Sequence(nBits, defaultState);

        MinTerm current;
        MinTerm next;
        bool isLoadingNextNotCurrent = false;
        bool skipping = false;
        while (!hasFoundEnd) {
            std::string tmpLD;
            inputStream >> tmpLD;

            if (tmpLD == "End") {
                hasFoundEnd = true;
                continue;
            }

            if (skipping) {
                skipping = false;
                continue;
            }

            if (!isLoadingNextNotCurrent) {
                current = std::stoi(tmpLD);
                isLoadingNextNotCurrent = true;
                skipping = true;
            } else {
                next = std::stoi(tmpLD);
                result.value().setNext(current, next);
                isLoadingNextNotCurrent = false;
            }
        }

        return result.value();
    }

    throw std::runtime_error("");
}
