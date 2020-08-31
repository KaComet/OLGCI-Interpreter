#include "PrintLexerComponent.h"

std::pair<std::string, Lexicon_Print> Lexicon_Print_Data[] = {
        std::make_pair("K-Maps", Lexicon_Print::K_Maps),
        std::make_pair("Excitation", Lexicon_Print::EXCITATION_TABLE)
};

const std::map<std::string, Lexicon_Print> lexicon_print(Lexicon_Print_Data, Lexicon_Print_Data +
                                                                             sizeof Lexicon_Print_Data /
                                                                             sizeof Lexicon_Print_Data[0]);

void PrintLexerComponent::run(std::ifstream &file, Environment &environment) {
    std::string tmp;
    file >> tmp;

    Lexicon_Print thisLexP;
    try {
        thisLexP = lexicon_print.at(tmp);
    } catch (std::out_of_range &e) {
        std::cout << "Symbol \"" << tmp << "\" not recognized. Exiting...";
        std::exit(1);
    }

    switch (thisLexP) {
        case Lexicon_Print::K_Maps:
            printSequenceAllK_Maps(file, environment);
            return;
        case Lexicon_Print::EXCITATION_TABLE:
            printSequenceExcitation(file, environment);
            return;
    }
}

void PrintLexerComponent::printSequenceAllK_Maps(std::ifstream &inputStream, Environment &environment) {
    while (!inputStream.eof()) {
        std::string tmp;
        inputStream >> tmp;

        Sequence &sq = environment.getVariable(tmp);
        for (unsigned int i = 0; i < sq.numberOfBits(); i++) {
            auto truthTableK = sq.makeTruthTable(i, false);
            auto truthTableJ = sq.makeTruthTable(i, true);
            std::cout << "\nK-Map for K" << i << std::endl;
            truthTableK.printKMap();

            std::cout << "\nK-Map for J" << i << std::endl;
            truthTableJ.printKMap();
        }

        return;
    }
}

void PrintLexerComponent::printSequenceExcitation(std::ifstream &inputStream, Environment &environment) {
    while (!inputStream.eof()) {
        std::string tmp;
        inputStream >> tmp;

        Sequence &sq = environment.getVariable(tmp);
        sq.printTable();

        return;
    }
}