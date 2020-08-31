#ifndef OLGCI_COMMON_H
#define OLGCI_COMMON_H

#include <cmath>
#include <string>
#include <stdexcept>

typedef unsigned int MinTerm;

enum class BIT_RESULT {
    ZERO = 0,
    ONE = 1,
    DONT_CARE = 2
};

namespace bit_result {
    static std::string toString(BIT_RESULT bitResult) {
        switch (bitResult) {
            case BIT_RESULT::ZERO:
                return "0";
            case BIT_RESULT::ONE:
                return "1";
            case BIT_RESULT::DONT_CARE:
                return "X";
        }

        throw std::runtime_error("");
    }
}

enum class Transition_State {
    ZeroToOne = 0,
    ZeroToZero = 1,
    OneToZero = 2,
    OneToOne = 3
};

struct JK_State {
public:
    JK_State() : j(BIT_RESULT::ZERO), k(BIT_RESULT::ZERO) {};

    JK_State(BIT_RESULT j, BIT_RESULT k) : j(j), k(k) {};
    BIT_RESULT j, k;

    static std::string toString(const JK_State &jkState) {
        return "J: " + bit_result::toString(jkState.j) + " K: " + bit_result::toString(jkState.k);
    }
};

unsigned int getBitmask(unsigned int nBits);

bool isMintermWithinRange(MinTerm);

unsigned int binaryToGray(unsigned int num);

std::string toBinaryString(unsigned int number, unsigned int nBits);

#endif //OLGCI_COMMON_H
