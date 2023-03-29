# Multi-Threaded Merge Sort

A Merge Sorter utilizing concurrency programming. The elements in the array to be sorted are initially randomly generated using the Mersenne Twister algorithm.

## Building

To build the executable `sort` run `make` or `make sort` in your terminal.

## Command Line Options

`$ ./sort [-l low] [-h high] [-s size] [-n elements] [-c cores] [-p]`

`-l low` and `-h high` specify the range `[low, high]` in which integers are randomly generated. Default: `[0, UINT32_MAX]`.

`-s size` specifies the size of the array to be sorted. Default: `100`

`-n elements` specifies the amount of elements to print when displaying the sorted array. Default: `100`

`-c cores` specifies the number of cores for multithreading. Default: `1`

`-p` enables parallel sorting.

## Benchmarks

Benchmarks with graphs are included in `WRITEUP.pdf`.
