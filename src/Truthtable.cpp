#include <iostream>
#include "Truthtable.h"

std::optional<BIT_RESULT> Truthtable::get(MinTerm minTerm) {
    for (const auto &m : truthTableData) {
        if (m.first == minTerm)
            return m.second;
    }

    return std::nullopt;
}

void Truthtable::set(MinTerm minTerm, BIT_RESULT output) {
    if (!isMintermWithinRange(minTerm))
        throw std::out_of_range("Minterm out of range of truth table.");

    for (auto &i : truthTableData) {
        if (i.first == minTerm) {
            i.first = minTerm;
            return;
        }
    }

    truthTableData.emplace_back(minTerm, output);
}

void Truthtable::printTable() {
    for (const auto &i : truthTableData) {
        printf("%s | %s\n", toBinaryString(i.first, nBits).c_str(), bit_result::toString(i.second).c_str());
    }
}

void Truthtable::printKMap() {
    TextTable t('-', '|', '-');
    unsigned int widthInBits = nBits / 2;
    unsigned int heightInBits = nBits - widthInBits;

    //std::string header = '(' + std::to_string(nBits - 1) + '-' + std::to_string(nBits - heightInBits) + ')' + \
                         '\\' + '(' +std::to_string(widthInBits - 1) + '-' + std::to_string(0) + ')';

    std::string header = " ";

    t.add(header);
    for (unsigned int j = 0; j <= getBitmask(widthInBits); j++) {
        t.add(toBinaryString(binaryToGray(j), widthInBits));
    }
    t.endOfRow();
    t.setAlignment(0, TextTable::Alignment::RIGHT);

    for (unsigned int i = 0; i <= getBitmask(heightInBits); i++) {
        unsigned int greyIndexVert = binaryToGray(i);
        t.add(toBinaryString(greyIndexVert, nBits - widthInBits));
        for (unsigned int j = 0; j <= getBitmask(widthInBits); j++) {
            unsigned int greyIndexHorz = binaryToGray(j);
            unsigned int greyIndex = (greyIndexVert << widthInBits) + greyIndexHorz;

            std::optional<BIT_RESULT> cellValue = get(greyIndex);

            if (!cellValue.has_value())
                cellValue = defaultOutput;

            t.add(bit_result::toString(cellValue.value()));
            t.setAlignment(j + 1, TextTable::Alignment::RIGHT);
        }
        t.endOfRow();
    }

    std::cout << t;
}
