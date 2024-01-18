#include "merge.h"

#include <iostream>
#include <vector>
#include <thread>
#include <iomanip>
#include <utility>

#define INF (-1)

void join_threads(std::vector<std::thread> &threads) {
    for (auto &t : threads) {
        t.join();
    }
}

void start_threads(std::vector<uint32_t> &A, uint32_t cores, std::vector<std::thread> &threads,
    std::vector<std::pair<uint32_t, uint32_t>> &indices) {
    uint32_t elements_per_thread = A.size() / cores;
    uint32_t remainder = A.size() % cores;
    void (*pf)(std::vector<uint32_t> &, uint32_t, uint32_t) = MergeSorter::mergeSort;
    uint32_t lo, hi;
    lo = hi = 0;
    for (uint32_t t = 0; t < cores; t += 1) {
        lo = hi + 1;
        hi = lo + elements_per_thread - 1;
        if (t < remainder) {
            hi += 1;
        }
        indices.emplace_back(lo, hi);

        std::thread thread(pf, std::ref(A), lo, hi);
        threads.push_back(std::move(thread));
    }
}

void threaded_merge_k_lists(std::vector<uint32_t> &A, uint32_t k, std::vector<std::thread> &threads,
    std::vector<std::pair<uint32_t, uint32_t>> &indices) {
    uint32_t lo, mid, hi;
    uint32_t step = 1;
    
    while (step < k) {
        threads.clear();
        for (uint32_t i = 0; i < k - step; i += step * 2) {
            lo = indices[i].first;
            hi = indices[i + step].second;
            mid = indices[i].second;
            std::thread thread(MergeSorter::merge, std::ref(A), lo, mid, hi);
            threads.push_back(std::move(thread));
            indices[i].second = hi;
        }
        join_threads(threads);
        step *= 2;
    }
}

void MergeSorter::merge(std::vector<uint32_t> &A, uint32_t p, uint32_t q, uint32_t r) {
    uint32_t left_size = q - p + 1;
    uint32_t right_size = r - q;

    std::vector<uint32_t> L(left_size + 1);
    std::vector<uint32_t> R(right_size + 1);

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
}

void MergeSorter::mergeSort(std::vector<uint32_t> &A, uint32_t p, uint32_t r) {
    uint32_t q;
    if (p < r) {
        q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        MergeSorter::merge(A, p, q, r);
    }
}

void MergeSorter::mergeSort(std::vector<uint32_t> &A) {
    mergeSort(A, 1, A.size());
}

void MergeSorter::parallelMergeSort(std::vector<uint32_t> &A, uint32_t cores) {
    std::vector<std::thread> threads {};
    std::vector<std::pair<uint32_t, uint32_t>> indices;
    start_threads(A, cores, threads, indices);
    join_threads(threads);
    threaded_merge_k_lists(A, cores, threads, indices);
}

void MergeSorter::display(std::vector<uint32_t> &A, uint32_t n) {
    if (n == 0) {
        return;
    }
    if (n > A.size()) {
        n = A.size();
    }
    for (uint32_t i = 0; i < n; i += 1) {
        if (i != 0 && (i % 5) == 0) {
            std::cout << "\n";
        }
        std::cout << std::setw(13) << A[i];
    }
    std::cout << "\n";
}
