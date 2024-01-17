#include "numgen.h"

#include <cstdint>
#include <random>


NumberGenerator::NumberGenerator() {
    lo = 0;
    hi = UINT32_MAX;
    gen.seed(std::random_device{}());
    distrib = std::uniform_int_distribution<uint32_t>(lo, hi);
}

NumberGenerator::NumberGenerator(uint32_t lo, uint32_t hi) {
    this->lo = lo;
    this->hi = hi;
    gen.seed(std::random_device{}());
    distrib = std::uniform_int_distribution<uint32_t>(this->lo, this->hi);
}

uint32_t NumberGenerator::number() {
    return distrib(gen);
}
