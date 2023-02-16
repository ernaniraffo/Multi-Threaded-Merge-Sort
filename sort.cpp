#include "merge.h"

#include <random>
#include <iostream>
#include <cinttypes>
#include <vector>
#include <iostream>
#include <getopt.h>
#include <set>
#include <chrono>

#define OPTIONS "l:h:s:mp"

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

int main(int argc, char** argv) {
    uint32_t lo = 0;
    uint32_t hi = 100;
    uint32_t size = 100;
    bool parallel = false;

    enum { MERGE, NUM_SORTS};
    std::set<int> s;

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'l': lo = strtoul(optarg, NULL, 10); break;
            case 'h': hi = strtoul(optarg, NULL, 10); break;
            case 's': size = strtoul(optarg, NULL, 10); break;
            case 'm': s.insert(MERGE); break;
            case 'p': parallel = true; break;
            default: break;
        }
    }

    std::vector<uint32_t> A = random_vector(lo, hi, size);

    if (s.contains(MERGE)) {
        if (parallel) {
            std::vector<uint32_t> B (A);
            auto start = std::chrono::steady_clock::now();
    
            MergeSorter::ParallelMergeSort(B);
            
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
        }

        auto start = std::chrono::steady_clock::now();

        MergeSorter::MergeSort(A);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }


    return 0;
}
