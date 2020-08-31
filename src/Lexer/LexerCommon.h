#ifndef TESTING_LEXERCOMMON_H
#define TESTING_LEXERCOMMON_H

#include <map>

/*

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
 */

/*
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

const std::map<std::string, Lexicon_Define> lexicon_define(Lexicon_Define_Data, Lexicon_Define_Data +
                                                                          sizeof Lexicon_Define_Data /
                                                                          sizeof Lexicon_Define_Data[0]);
const std::map<std::string, Lexicon_Define_SEQUENCE> Lexicon_Define_SEQUENCE(Lexicon_Define_SEQUENCE_Data,
                                                                       Lexicon_Define_SEQUENCE_Data +
                                                                       sizeof Lexicon_Define_SEQUENCE_Data /
                                                                       sizeof Lexicon_Define_SEQUENCE_Data[0]);
const std::map<std::string, Lexicon_Print> lexicon_print(Lexicon_Print_Data, Lexicon_Print_Data +
                                                                       sizeof Lexicon_Print_Data /
                                                                       sizeof Lexicon_Print_Data[0]);
                                                                       */

#endif //TESTING_LEXERCOMMON_H
