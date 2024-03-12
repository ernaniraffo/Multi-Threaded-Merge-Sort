#pragma once

#include <cstdint>
#include <random>
#include <vector>

class MergeSorter {
  public:
    static void merge(std::vector<uint32_t>&, uint32_t, uint32_t, uint32_t);
    static void mergeSort(std::vector<uint32_t>&);
    static void mergeSort(std::vector<uint32_t>&, uint32_t, uint32_t);
    static void parallelMergeSort(std::vector<uint32_t>&, uint32_t);
    static void display(std::vector<uint32_t>&, uint32_t);
};
