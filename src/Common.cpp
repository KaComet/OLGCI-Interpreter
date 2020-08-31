#include "Common.h"

unsigned int getBitmask(unsigned int nBits) {
    if (nBits == 0)
        return 0;
    else
        return ((unsigned int)pow(2, nBits - 1)) + getBitmask(nBits - 1);
}

bool isMintermWithinRange(MinTerm minTerm) {
    return (getBitmask(minTerm) & minTerm) == minTerm;
}

unsigned int binaryToGray(unsigned int num) {
    return num ^ (num >> 1); // The operator >> is shift right. The operator ^ is exclusive or.
}

std::string toBinaryString(unsigned int number, unsigned int nBits) {
    std::string result;
    for (unsigned int i = 0; i < nBits; i++) {
        bool isOne = number & ((unsigned int)0b1 << i);
        if (isOne)
            result = '1' + result;
        else
            result = '0' + result;
    }

    return result;
}