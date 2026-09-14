// Incorrect: signed ordering puts values >= 2^63 first.
#include <algorithm>
#include "solve.hpp"

void solve(std::vector<uint64_t>& a) {
    std::sort(a.begin(), a.end(), [](uint64_t x, uint64_t y) {
        return (x ^ (uint64_t(1) << 63)) < (y ^ (uint64_t(1) << 63));
    });
}
