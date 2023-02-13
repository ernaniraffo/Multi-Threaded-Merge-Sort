#include "quick.h"
#include <random>
#include <iostream>
#include <cinttypes>
#include <vector>
#include <iostream>

std::vector<uint32_t> random_vector(uint32_t lo, uint32_t hi, uint32_t len) {
    std::vector<uint32_t> A;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> distrib(lo, hi);

    for (uint32_t i = 0; i < len; i += 1) {
        A.push_back(distrib(gen));
    }
    return A;
}

void printVector(std::vector<uint32_t> &A) {
    std::cout << "[ ";
    for (auto const& n : A) {
        std::cout << n << ", ";
    }
    std::cout << "]\n";
    return;
}

int main() {
    uint32_t lo = 0;
    uint32_t hi = 50;
    uint32_t len = 50;
    std::vector<uint32_t> A = random_vector(lo, hi, len);
    printVector(A);
    quick_sort(A);
    printVector(A);
    return 0;
}
