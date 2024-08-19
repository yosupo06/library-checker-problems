#include <algorithm>
#include <cstdio>
#include <vector>

#include "../binary_mat.h"
#include "../intersection.h"

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

int bitrev30(int x) {
    int res = 0;
    for (int i = 0; i < 30; i++) {
        res = res << 1 | (x & 1);
        x >>= 1;
    }
    return res;
}

int main(void) {
    int T;
    std::scanf("%d", &T);

    while (T--) {
        size_t n, m;
        std::scanf("%zu", &n);
        std::vector<int> u(n);
        REP(i, 0, n) {
            std::scanf("%d", &u[i]);
        }
        std::scanf("%zu", &m);
        std::vector<int> v(m);
        REP(i, 0, m) {
            std::scanf("%d", &v[i]);
        }
        for (int &x: u) x = bitrev30(x);
        for (int &x: v) x = bitrev30(x);
        auto intersection_basis = intersection(u, v);
        for (int &x: intersection_basis) x = bitrev30(x);
        printf("%zu", intersection_basis.size());
        for (int b: intersection_basis) {
            printf(" %d", b);
        }
        puts("");
    }
}
