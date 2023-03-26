#include "threads.h"
#include <thread>
#include <vector>

void JoinThreads(std::vector<std::thread> &threads) {
    for (auto &t : threads) {
        t.join();
    }
    return;
}