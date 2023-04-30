#include <chrono>
#include <iostream>

#include "fastio.h"
#include "solve.hpp"

using namespace std::chrono;
using namespace library_checker;

Scanner sc = Scanner(stdin);
Printer pr = Printer(stdout);

int main() {
    int n, m;
    sc.read(n, m);

    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        sc.read(a[i]);
    }
    for (int i = 0; i < m; i++) {
        sc.read(b[i]);
    }

    steady_clock::time_point begin = steady_clock::now();
    auto ans = solve(a, b);
    steady_clock::time_point end = steady_clock::now();

    auto elapsed_time = duration_cast<milliseconds>(end - begin);
    std::cerr << "solve() consumes: " << elapsed_time.count() << "ms"
              << std::endl;

    for (int i = 0; i <= (n - 1) + (m - 1); i++) {
        if (i) pr.write(' ');
        pr.write(ans[i]);
    }
    pr.writeln();

    return 0;
}
