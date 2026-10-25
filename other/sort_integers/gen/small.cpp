#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <vector>
#include "fastio.h"
#include "random.h"

int main(int, char** argv) {
    Random rng(std::atoll(argv[1]));
    library_checker::Printer pr(stdout);
    const uint64_t top = std::numeric_limits<uint64_t>::max();
    std::vector<uint64_t> boundary{0, 1, top};
    for (int b = 1; b < 64; ++b) {
        boundary.push_back((uint64_t(1) << b) - 1);
        boundary.push_back(uint64_t(1) << b);
        boundary.push_back((uint64_t(1) << b) + 1);
    }
    pr.writeln(400);
    for (int t = 0; t < 400; ++t) {
        int n = t < 260 ? t + 1 : rng.uniform(1, 2049);
        pr.writeln(n);
        for (int i = 0; i < n; ++i) {
            if (i) pr.write(' ');
            pr.write(t % 2 ? rng.uniform<uint64_t>(0, top) : boundary[rng.uniform(0, int(boundary.size()) - 1)]);
        }
        pr.writeln();
    }
}
