#include "arraygen.h"

ArrayGenerator::ArrayGenerator() {
    rng = NumberGenerator();
}

ArrayGenerator::ArrayGenerator(uint32_t lo, uint32_t hi) {
    rng = NumberGenerator(lo, hi);
}

void ArrayGenerator::arrayGen(std::vector<uint32_t> &A) {
    for (int i = 0; i < (int) A.size(); i += 1) {
        A[i] = rng.number();
    }
}
