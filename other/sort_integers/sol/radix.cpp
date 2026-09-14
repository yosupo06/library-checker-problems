#include <algorithm>
#include <array>
#include "solve.hpp"

void solve(std::vector<uint64_t>& a) {
    if (a.size() < 128) {
        std::sort(a.begin(), a.end());
        return;
    }
    std::vector<uint64_t> b(a.size());
    // Stable least-significant-digit radix sort, eight byte-sized passes.
    for (int shift = 0; shift < 64; shift += 8) {
        std::array<size_t, 256> next{};
        for (auto x : a) ++next[(x >> shift) & 255];
        size_t sum = 0;
        for (auto& count : next) {
            size_t old = count;
            count = sum;
            sum += old;
        }
        for (auto x : a) b[next[(x >> shift) & 255]++] = x;
        a.swap(b);
    }
}
