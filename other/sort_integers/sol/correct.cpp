#include <algorithm>
#include <cstdint>
#include <vector>
#include "fastio.h"

int main() {
    library_checker::Scanner sc(stdin);
    library_checker::Printer pr(stdout);
    int t;
    sc.read(t);
    while (t--) {
        int n;
        sc.read(n);
        std::vector<uint64_t> a(n);
        for (auto& x : a) sc.read(x);
        std::sort(a.begin(), a.end());
        for (int i = 0; i < n; ++i) {
            if (i) pr.write(' ');
            pr.write(a[i]);
        }
        pr.writeln();
    }
}
