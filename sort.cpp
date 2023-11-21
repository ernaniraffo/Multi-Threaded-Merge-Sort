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
#include <algorithm>
#include <functional>
#include <assert.h>

#define OPTIONS "l:h:s:n:c:p"

std::string usage();

int main(int argc, char **argv) {
    uint32_t lo = 0;
    uint32_t hi = UINT32_MAX;
    uint32_t size = 100;
    uint32_t n = 100;
    uint32_t cores = 1;
    bool parallel = false;

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'l': lo = strtoul(optarg, NULL, 10); break;
        case 'h': hi = strtoul(optarg, NULL, 10); break;
        case 's': size = strtoul(optarg, NULL, 10); break;
        case 'n': n = strtoul(optarg, NULL, 10); break;
        case 'c': cores = strtoul(optarg, NULL, 10); break;
        case 'p': parallel = true; break;
        default: std::cerr << usage(); return EXIT_FAILURE;
        }
    }

    if (cores > std::thread::hardware_concurrency()) {
        throw std::invalid_argument("cores specfied exceeds available");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> distrib(lo, hi);

    std::vector<uint32_t> A(size);

    auto sort = [&](bool parallel) {
        MergeSorter::RandomArray(A);
    
        auto start = std::chrono::steady_clock::now();
        parallel ? MergeSorter::ParallelMergeSort(A, cores) : MergeSorter::MergeSort(A);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        std::string type = parallel ? "Parallel Merge Sort" : "Merge Sort";
        std::cout << type << ", " << A.size() << " elements, " << elapsed_seconds.count() << " seconds\n";
        MergeSorter::Display(A, n);
    };

    sort(parallel);

    return EXIT_SUCCESS;
}

std::string usage() {
    return std::string {} 
            + "Synopsis\n" 
            + "\tA Merge Sorter utilizing concurrency programming.\n"
            + "Usage\n" 
            + "\t./sort [-l low] [-h high] [-s size] [-n elements] [-c cores] [-p]\n"
            + "Options\n" 
            + "\t-l low        lower bound for number generation. Default: 0\n"
            + "\t-h high       higher bound for number generation. Default: UINT32_MAX\n"
            + "\t-s size       size of array to sort\n"
            + "\t-n elements   elements to be displayed once sorted. Default: 100\n"
            + "\t-c cores      number of cores for multithreading. Default: 1\n"
            + "\t-p            enables parallel sorting\n";
}
