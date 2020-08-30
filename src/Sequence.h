#ifndef OLGCI_SEQUENCE_H
#define OLGCI_SEQUENCE_H

#include "Common.h"
#include <vector>
#include <iostream>
#include <bitset>
#include <stdexcept>
#include <cmath>
#include "Truthtable.h"
#include <TextTable.h>

class Sequence {
public:
    Sequence() = delete;

    explicit Sequence(unsigned int nBits, MinTerm defaultState = 0) : nBits(nBits), defaultState(defaultState) {
        for (unsigned int i = 0; i <= getBitmask(nBits); i++) {
            sequenceData.emplace_back(std::pair<MinTerm, MinTerm>(i, defaultState));
        }
    };

    void setNext(MinTerm state, MinTerm next);

    MinTerm getNext(MinTerm state);

    [[nodiscard]] JK_State getJK(MinTerm state, unsigned int bitNumber) const;

    void printTable();

    [[nodiscard]] Truthtable makeTruthTable(unsigned int bitNumber, bool gettingJ_Not_K) const;

    [[nodiscard]] unsigned int numberOfBits() const noexcept {
        return nBits;
    }

private:
    std::vector<std::pair<MinTerm, MinTerm>> sequenceData;
    MinTerm defaultState;
    unsigned int nBits;
};


#endif //OLGCI_SEQUENCE_H
