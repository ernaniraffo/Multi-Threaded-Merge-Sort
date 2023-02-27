#include "merge.h"

#include <random>
#include <iostream>
#include <cinttypes>
#include <vector>
#include <iostream>
#include <getopt.h>
#include <set>
#include <chrono>
#include <thread>
#include <stdexcept>

#define OPTIONS "l:h:s:n:c:mp"

int main(int argc, char** argv) {
    uint32_t lo = 0;
    uint32_t hi = UINT32_MAX;
    uint32_t size = 100;
    uint32_t n = 100;
    uint32_t cores = 1;
    bool parallel = false;

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'l': lo    = strtoul(optarg, NULL, 10); break;
            case 'h': hi    = strtoul(optarg, NULL, 10); break;
            case 's': size  = strtoul(optarg, NULL, 10); break;
            case 'n': n     = strtoul(optarg, NULL, 10); break;
            case 'c': cores = strtoul(optarg, NULL, 10); break;
            case 'p': parallel = true; break;
            default: break;
        }
    }

    if (cores > std::thread::hardware_concurrency()) {
        throw std::invalid_argument("cores specfied exceeds available");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> distrib(lo, hi);

    std::vector<uint32_t> A (size);

    if (parallel) {

        MergeSorter::RandomArray(A, gen, distrib);
        
        auto start = std::chrono::steady_clock::now();
        MergeSorter::ParallelMergeSort(A, cores);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        
        std::cout << "Parallel Merge Sort, " << size << " elements, " << elapsed_seconds.count() << " seconds\n";
        MergeSorter::Display(A, n);
    }

    MergeSorter::RandomArray(A, gen, distrib);

    auto start = std::chrono::steady_clock::now();
    MergeSorter::MergeSort(A);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    std::cout << "Merge Sort, " << size << " elements, " << elapsed_seconds.count() << " seconds\n";
    MergeSorter::Display(A, n);

    return EXIT_SUCCESS;
}
