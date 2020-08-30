#include <iostream>
#include "src/Common.h"
#include "src/Sequence.h"
#include <map>
#include <fstream>

/*This file implements a simple lexer for processing file formatted in OLGCI script.*/

enum class Lexicon {
    Define,
    Print,
};

enum class Lexicon_Define {
    Sequence
};

enum class Lexicon_Define_SEQUENCE {
    End
};

enum class Lexicon_Print {
    K_Maps,
    EXCITATION_TABLE
};

Sequence loadSequence(std::ifstream &inputStream);

void define(std::ifstream &inputStream, std::map<std::string, Lexicon_Define> &lexicon_define,
            std::map<std::string, Sequence> &environment_sequences);

void print(std::ifstream &inputStream, std::map<std::string, Lexicon_Print> &lexicon_print,
           std::map<std::string, Sequence> &environment_sequences);

void printSequenceAllK_Maps(std::ifstream &inputStream, std::map<std::string, Sequence> &environment_sequences);

void printSequenceExcitation(std::ifstream &inputStream, std::map<std::string, Sequence> &environment_sequences);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Requires an input file path. Exiting...";
        exit(1);
    }

    std::string filePath = argv[1];

    std::map<std::string, Sequence> environment_sequences;

    std::pair<std::string, Lexicon> lexicon_data[] = {
            std::make_pair("Define", Lexicon::Define),
            std::make_pair("Print", Lexicon::Print),
    };

    std::pair<std::string, Lexicon_Define> Lexicon_Define_Data[] = {
            std::make_pair("Sequence", Lexicon_Define::Sequence)
    };

    std::pair<std::string, Lexicon_Define_SEQUENCE> Lexicon_Define_SEQUENCE_Data[] = {
            std::make_pair("End", Lexicon_Define_SEQUENCE::End)
    };

    std::pair<std::string, Lexicon_Print> Lexicon_Print_Data[] = {
            std::make_pair("K-Maps", Lexicon_Print::K_Maps),
            std::make_pair("Excitation", Lexicon_Print::EXCITATION_TABLE)
    };

    std::map<std::string, Lexicon> lexicon(lexicon_data, lexicon_data + sizeof lexicon_data / sizeof lexicon_data[0]);
    std::map<std::string, Lexicon_Define> lexicon_define(Lexicon_Define_Data, Lexicon_Define_Data +
                                                                              sizeof Lexicon_Define_Data /
                                                                              sizeof Lexicon_Define_Data[0]);
    std::map<std::string, Lexicon_Define_SEQUENCE> Lexicon_Define_SEQUENCE(Lexicon_Define_SEQUENCE_Data,
                                                                           Lexicon_Define_SEQUENCE_Data +
                                                                           sizeof Lexicon_Define_SEQUENCE_Data /
                                                                           sizeof Lexicon_Define_SEQUENCE_Data[0]);
    std::map<std::string, Lexicon_Print> lexicon_print(Lexicon_Print_Data, Lexicon_Print_Data +
                                                                           sizeof Lexicon_Print_Data /
                                                                           sizeof Lexicon_Print_Data[0]);

    std::ifstream file;
    file.open(filePath);

    if (file.is_open()) {
        while (!file.eof()) {
            std::string tmp;
            file >> tmp;
            Lexicon thisLex;

            if (tmp.empty())
                continue;

            try {
                thisLex = lexicon.at(tmp);
            } catch (std::out_of_range &e) {
                std::cout << "Symbol \"" << tmp << "\" not recognized. Exiting...";
                std::exit(1);
            }

            switch (thisLex) {
                case Lexicon::Define:
                    define(file, lexicon_define, environment_sequences);
                    break;


                case Lexicon::Print:
                    print(file, lexicon_print, environment_sequences);
                    break;
            }


        }
    } else {
        std::cout << "Input file could not be loaded.";
    }

    return 0;
}

void define(std::ifstream &inputStream, std::map<std::string, Lexicon_Define> &lexicon_define,
            std::map<std::string, Sequence> &environment_sequences) {
    std::string tmpD;
    inputStream >> tmpD;

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
            inputStream >> tmpSQ;
            environment_sequences.emplace(tmpSQ, loadSequence(inputStream));
            break;
    }
}

Sequence loadSequence(std::ifstream &inputStream) {
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

void print(std::ifstream &inputStream, std::map<std::string, Lexicon_Print> &lexicon_print,
           std::map<std::string, Sequence> &environment_sequences) {
    while (!inputStream.eof()) {
        std::string tmp;
        inputStream >> tmp;

        Lexicon_Print thisLexP;
        try {
            thisLexP = lexicon_print.at(tmp);
        } catch (std::out_of_range &e) {
            std::cout << "Symbol \"" << tmp << "\" not recognized. Exiting...";
            std::exit(1);
        }

        switch (thisLexP) {
            case Lexicon_Print::K_Maps:
                printSequenceAllK_Maps(inputStream, environment_sequences);
                return;
            case Lexicon_Print::EXCITATION_TABLE:
                printSequenceExcitation(inputStream, environment_sequences);
                return;
        }
    }
}

void printSequenceAllK_Maps(std::ifstream &inputStream, std::map<std::string, Sequence> &environment_sequences) {
    while (!inputStream.eof()) {
        std::string tmp;
        inputStream >> tmp;

        Sequence &sq = environment_sequences.at(tmp);
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

void printSequenceExcitation(std::ifstream &inputStream, std::map<std::string, Sequence> &environment_sequences) {
    while (!inputStream.eof()) {
        std::string tmp;
        inputStream >> tmp;

        Sequence &sq = environment_sequences.at(tmp);
        sq.printTable();

        return;
    }
}