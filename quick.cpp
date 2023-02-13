#include "quick.h"
#include <vector>
#include <cinttypes>

void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
    return;
}

uint32_t partition(std::vector<uint32_t> &A, uint32_t p, uint32_t r) {
    uint32_t pivot = A[r - 1];
    uint32_t i = p - 1;
    for (uint32_t j = p; j < r; j += 1) {
        if (A[j - 1] <= pivot) {
            i += 1;
            swap(&A[i -1], &A[j - 1]); 
        }
    }
    swap(&A[i], &A[r - 1]);
    return i + 1;
}

void sorter(std::vector<uint32_t> &A, uint32_t p, uint32_t r) {
    uint32_t q;
    if (p < r) {
        q = partition(A, p, r);
        sorter(A, p, q - 1);
        sorter(A, q + 1, r);
    }
    return;
}

void quick_sort(std::vector<uint32_t> &A) {
    sorter(A, 1, A.size());
    return;
}