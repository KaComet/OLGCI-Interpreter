#ifndef OLGCI_TRUTHTABLE_H
#define OLGCI_TRUTHTABLE_H

#include <bitset>
#include <vector>
#include <optional>
#include <stdexcept>
#include <TextTable.h>
#include "Common.h"

class Truthtable {
public:
    Truthtable() = delete;

    explicit Truthtable(unsigned int nBits, BIT_RESULT defaultOutput = BIT_RESULT::ZERO) : nBits(nBits),
                                                                                           defaultOutput(defaultOutput)
                                                                                           {};

    std::optional<BIT_RESULT> get(MinTerm minTerm);

    void set(MinTerm minTerm, BIT_RESULT output);

    void printTable();

    void printKMap();

private:
    std::vector<std::pair<MinTerm, BIT_RESULT>> truthTableData;
    BIT_RESULT defaultOutput;
    unsigned int nBits;
};


#endif //OLGCI_TRUTHTABLE_H
