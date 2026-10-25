#include <chrono>
#include <cstdio>
#include "fastio.h"
#include "solve.hpp"

int main() {
    library_checker::Scanner sc(stdin);
    library_checker::Printer pr(stdout);
    int t;
    sc.read(t);
    std::vector<std::vector<uint64_t>> arrays(t);
    for (auto& a : arrays) {
        int n;
        sc.read(n);
        a.resize(n);
        for (auto& x : a) sc.read(x);
    }
    auto begin = std::chrono::steady_clock::now();
    for (auto& a : arrays) solve(a);
    auto end = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double, std::milli>(end - begin).count();
    std::fprintf(stderr, "solve() consumes: %.3fms\n", elapsed);
    for (const auto& a : arrays) {
        for (int i = 0; i < int(a.size()); ++i) {
            if (i) pr.write(' ');
            pr.write(a[i]);
        }
        pr.writeln();
    }
}
