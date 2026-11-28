// Incorrect: ignores the upper half of each key.
#include <algorithm>
#include "solve.hpp"

void solve(std::vector<uint64_t>& a) {
    std::sort(a.begin(), a.end(), [](uint64_t x, uint64_t y) {
        return uint32_t(x) < uint32_t(y);
    });
}
