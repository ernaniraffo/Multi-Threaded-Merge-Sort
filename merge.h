#pragma once
#include <vector>
#include <cinttypes>
#include <random>

class MergeSorter {
private:
    static void Merge(std::vector<uint32_t> &, uint32_t, uint32_t, uint32_t);

public:
    static void RandomArray(
        std::vector<uint32_t> &, std::mt19937 &, std::uniform_int_distribution<unsigned long> &);
    static void MergeSort(std::vector<uint32_t> &);
    static void MergeSort(std::vector<uint32_t> &, uint32_t, uint32_t);
    static void ParallelMergeSort(std::vector<uint32_t> &, uint32_t);
    static void Display(std::vector<uint32_t> &, uint32_t);
};
