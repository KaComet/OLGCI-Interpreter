#include "Sequence.h"

void Sequence::setNext(MinTerm state, MinTerm next) {
    if ((!isMintermWithinRange(state)) || (!isMintermWithinRange(next)))
        throw std::out_of_range("Minterm out of range of sequence table.");

    for (auto &e : sequenceData) {
        if (e.first == state) {
            e.second = next;
            return;
        }
    }

    throw std::runtime_error("Minterm could not be found in sequence.");
}

MinTerm Sequence::getNext(MinTerm state) {
    if (!isMintermWithinRange(state))
        throw std::out_of_range("Minterm out of range of sequence table.");

    for (auto &e : sequenceData) {
        if (e.first == state) {
            return e.second;
        }
    }

    throw std::runtime_error("Minterm could not be found in sequence.");
}

JK_State Sequence::getJK(MinTerm state, unsigned int bitNumber) const {
    if (!isMintermWithinRange(state))
        throw std::out_of_range("Minterm out of range of sequence table.");

    if (bitNumber >= nBits)
        throw std::out_of_range("Bit number is out of range of sequence table.");

    for (auto &e : sequenceData) {
        if (e.first == state) {
            BIT_RESULT start = BIT_RESULT::ZERO;
            BIT_RESULT end = BIT_RESULT::ZERO;

            if ((unsigned int) std::pow(2, bitNumber) & e.first)
                start = BIT_RESULT::ONE;

            if ((unsigned int) std::pow(2, bitNumber) & e.second)
                end = BIT_RESULT::ONE;

            if ((start == BIT_RESULT::ONE) && (end == BIT_RESULT::ONE))
                return JK_State(BIT_RESULT::DONT_CARE, BIT_RESULT::ZERO);

            if ((start == BIT_RESULT::ONE) && (end == BIT_RESULT::ZERO))
                return JK_State(BIT_RESULT::DONT_CARE, BIT_RESULT::ONE);

            if ((start == BIT_RESULT::ZERO) && (end == BIT_RESULT::ONE))
                return JK_State(BIT_RESULT::ONE, BIT_RESULT::DONT_CARE);

            if ((start == BIT_RESULT::ZERO) && (end == BIT_RESULT::ZERO))
                return JK_State(BIT_RESULT::ZERO, BIT_RESULT::DONT_CARE);
        }
    }

    throw std::runtime_error("Minterm could not be found in sequence.");
}

void Sequence::printTable() {
    printf("State | JK_max, JK_max-1... | Next\n");
    for (unsigned int i = 0; i <= getBitmask(nBits); i++) {
        printf("%s", toBinaryString(i, nBits).c_str());
        for (unsigned j = nBits; j > 0; j--) {
            JK_State jkTmp = getJK(i, j - 1);
            printf(" | %s %s", bit_result::toString(jkTmp.j).c_str(), bit_result::toString(jkTmp.k).c_str());
        }
        printf(" | %s\n", toBinaryString(getNext(i), nBits).c_str());
    }
}

Truthtable Sequence::makeTruthTable(unsigned int bitNumber, bool gettingJ_Not_K) const {
    if (bitNumber >= nBits)
        throw std::out_of_range("Bit number is out of range of sequence table.");

    Truthtable result = Truthtable(nBits);

    for (auto &e : sequenceData) {
        JK_State tmpJK = getJK(e.first, bitNumber);
        BIT_RESULT tmpBit = BIT_RESULT::ZERO;
        if (gettingJ_Not_K)
            tmpBit = tmpJK.j;
        else
            tmpBit = tmpJK.k;

        result.set(e.first, tmpBit);
    }

    return result;
}
