#include "merge.h"

#include <iostream>
#include <vector>
#include <cinttypes>

#define INF -1

void merge(std::vector<uint32_t>& A, uint32_t p, uint32_t q, uint32_t r) {
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

void merge_sort(std::vector<uint32_t>& A, uint32_t p, uint32_t r) {
    uint32_t q;
    if (p < r) {
        q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void merge_sort(std::vector<uint32_t>& A) {
    merge_sort(A, 1, A.size());
    return;
}