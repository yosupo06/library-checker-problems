#include <cstdint>
#include <cstdlib>
#include <limits>
#include <vector>
#include "fastio.h"
#include "random.h"
#include "../params.h"

int main(int, char** argv) {
    int type = std::atoi(argv[1]);
    Random rng(type + 100);
    std::vector<int> lengths;
    int remaining = N_SUM_MAX;
    if (type == 0) {
        lengths.assign(T_MAX, int(N_SUM_MAX / T_MAX));
        for (int i = 0; i < N_SUM_MAX % T_MAX; ++i) ++lengths[i];
        rng.shuffle(lengths.begin(), lengths.end());
        remaining = 0;
    }
    while (remaining) {
        int n;
        if (type == 1) n = (1 << rng.uniform(7, 16)) + rng.uniform(-1, 1);
        else n = lengths.size() % 2 ? rng.uniform(1024, 65536) : 1;
        if (int(lengths.size()) == T_MAX - 1) n = remaining;
        n = std::min(n, remaining);
        lengths.push_back(n);
        remaining -= n;
    }
    library_checker::Printer pr(stdout);
    pr.writeln(int(lengths.size()));
    for (int n : lengths) {
        pr.writeln(n);
        for (int i = 0; i < n; ++i) {
            if (i) pr.write(' ');
            pr.write(rng.uniform<uint64_t>(0, std::numeric_limits<uint64_t>::max()));
        }
        pr.writeln();
    }
}
