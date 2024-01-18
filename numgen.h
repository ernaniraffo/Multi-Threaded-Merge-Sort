#pragma once

#include <cstdint>
#include <random>

class NumberGenerator {
public:
    NumberGenerator();
    NumberGenerator(uint32_t lo, uint32_t hi);
    uint32_t number();

private:
    uint32_t lo;
    uint32_t hi;
    std::mt19937 gen;
    std::uniform_int_distribution<uint32_t> distrib;
};
