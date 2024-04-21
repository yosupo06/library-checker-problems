#include <algorithm>
#include <iostream>
#include <vector>

#include "../binary_mat.h"
#include "../intersection.h"

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T--) {
        size_t n, m;
        std::cin >> n;
        std::vector<int> u(n);
        REP(i, 0, n) {
            std::cin >> u[i];
        }
        std::cin >> m;
        std::vector<int> v(m);
        REP(i, 0, m) {
            std::cin >> v[i];
        }
        auto intersection_basis = intersection(u, v);
        std::cout << intersection_basis.size();
        for (int b: intersection_basis) {
            std::cout << " " << b;
        }
        std::cout << "\n";
    }
}
