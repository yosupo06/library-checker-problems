#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <vector>
#include "fastio.h"
#include "random.h"
#include "../params.h"

int main(int, char** argv) {
    int type = std::atoi(argv[1]);
    Random rng(type);
    int n = type < 3 ? int(N_SUM_MAX) : (1 << 18);
    const uint64_t top = std::numeric_limits<uint64_t>::max();
    std::vector<uint64_t> a(n);
    for (auto& x : a) x = rng.uniform<uint64_t>(0, top);
    if (type == 1 || type == 2 || type == 3) {
        std::sort(a.begin(), a.end());
        if (type == 2) std::reverse(a.begin(), a.end());
        if (type == 3) for (int i = 0; i < 100; ++i) std::swap(a[rng.uniform(0, n - 1)], a[rng.uniform(0, n - 1)]);
    } else if (type == 4) {
        std::fill(a.begin(), a.end(), top);
    } else if (type == 5) {
        for (auto& x : a) x = (x % 4) * (top / 3);
    } else if (type == 6) {
        for (auto& x : a) if (x % 100) x = 0;
    } else if (type == 7) {
        for (auto& x : a) x = (top << 16) | (x & 65535);
    } else if (type == 8) {
        for (auto& x : a) x = (x & 65535) << 48;
    } else if (type == 9) {
        for (int i = 0; i < n; i += 1024) std::sort(a.begin() + i, a.begin() + std::min(n, i + 1024));
    } else if (type == 10) {
        for (int i = 0; i < n; ++i) a[i] = uint64_t(std::min(i, n - 1 - i));
    } else if (type == 11) {
        for (int i = 0; i < n; ++i) a[i] = uint64_t(i % 257) << 32;
    }
    library_checker::Printer pr(stdout);
    pr.writeln(1);
    pr.writeln(n);
    for (int i = 0; i < n; ++i) {
        if (i) pr.write(' ');
        pr.write(a[i]);
    }
    pr.writeln();
}
