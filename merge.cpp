#include "merge.h"

#include <iostream>
#include <vector>
#include <cinttypes>
#include <thread>

#define MAX(a, b) (a > b ? a : b)
#define INF -1
#define NUM_THREADS 4

void MergeSorter::Merge(std::vector<uint32_t>& A, uint32_t p, uint32_t q, uint32_t r) {
    uint32_t left_size = q - p + 1;
    uint32_t right_size = r - q;
    
    std::vector<uint32_t> L (left_size + 1);
    std::vector<uint32_t> R (right_size + 1);
    
    for (uint32_t i = 1; i <= left_size; i += 1) {
        L[i - 1] = A[p + i - 2];
    }

    for (uint32_t j = 1; j <= right_size; j += 1) {
        R[j - 1] = A[q + j - 1];
    }

    L[left_size] = INF;
    R[right_size] = INF;

    uint32_t i = 1;
    uint32_t j = 1;

    for (uint32_t k = p; k <= r; k += 1) {
        if (L[i - 1] <= R[j - 1]) {
            A[k - 1] = L[i - 1];
            i += 1;
        } else {
            A[k - 1] = R[j - 1];
            j += 1;
        }
    }

    return;
}

void MergeSorter::MergeSort(std::vector<uint32_t>& A, uint32_t p, uint32_t r) {
    uint32_t q;
    if (p < r) {
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        MergeSorter::Merge(A, p, q, r);
    }
}

void MergeSorter::MergeSort(std::vector<uint32_t>& A) {
    MergeSort(A, 1, A.size());
    return;
}

void MergeSorter::ParallelMergeSort(std::vector<uint32_t>& A) {
    std::vector<std::thread> threads {};
    
    void (*pf)(std::vector<uint32_t>&, uint32_t, uint32_t) = MergeSort;
    
    uint32_t elements_per_thread = A.size() / NUM_THREADS;
    for (uint32_t t = 0; t < NUM_THREADS; t += 1) {
        uint32_t p = (t * elements_per_thread) + 1;
        uint32_t r = ((t + 1) * (elements_per_thread));
        std::thread thread (pf, std::ref(A), p, r);
        threads.push_back(std::move(thread));
    }

    for (auto &t : threads) {
        t.join();
    }

    uint32_t lo = 1;
    uint32_t mid = elements_per_thread;
    uint32_t max = mid * 2;
    
    Merge(A, lo, mid, max);
    
    lo = max + 1;
    mid += max;
    max = elements_per_thread * 4;

    Merge(A, lo, mid, max);

    Merge(A, 1, max / 2, max);

    return;
}