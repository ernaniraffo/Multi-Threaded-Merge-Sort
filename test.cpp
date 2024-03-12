#include "arraygen.h"
#include "numgen.h"

#include <iostream>

int main(void) {
    NumberGenerator rng = NumberGenerator(0, 500);

    uint32_t lo = rng.number();
    uint32_t hi = rng.number();
    while (hi < lo) {
        hi = rng.number();
    }

    for (int i = 0; i < 10; i += 1) {
        std::cout << rng.number() << "\n";
    }

    ArrayGenerator array_generator = ArrayGenerator(lo, hi);
    std::vector<uint32_t> A(50);
    array_generator.arrayGen(A);

    std::cout << "lo = " << lo << ", hi = " << hi << "\n";
    std::cout << "[";
    for (int i = 0; i < (int) A.size(); i += 1) {
        std::cout << A[i] << (i + 1 == (int) A.size() ? "" : ", ");
    }
    std::cout << "]\n";

    return 0;
}