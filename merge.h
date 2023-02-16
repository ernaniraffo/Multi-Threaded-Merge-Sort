#pragma once
#include <vector>
#include <cinttypes>

class MergeSorter {
    private:
        static void Merge(std::vector<uint32_t>&, uint32_t, uint32_t, uint32_t);
    public:
        static void MergeSort(std::vector<uint32_t>&);
        static void MergeSort(std::vector<uint32_t>&, uint32_t, uint32_t);
        static void ParallelMergeSort(std::vector<uint32_t>&);
};