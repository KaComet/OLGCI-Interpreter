#include "src/Truthtable.h"

int main() {
    Truthtable a(3);
    a.set(0, BIT_RESULT::ONE);
    a.set(1, BIT_RESULT::ZERO);
    a.set(2, BIT_RESULT::ONE);
    a.set(3, BIT_RESULT::ZERO);
    a.set(4, BIT_RESULT::DONT_CARE);
    a.set(5, BIT_RESULT::DONT_CARE);
    a.set(6, BIT_RESULT::DONT_CARE);
    a.set(7, BIT_RESULT::DONT_CARE);

    a.printKMap();
}