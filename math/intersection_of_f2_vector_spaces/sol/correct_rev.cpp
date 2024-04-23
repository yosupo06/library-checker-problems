#include <algorithm>
#include <cstdio>
#include <vector>

#include "../binary_mat.h"
#include "../intersection.h"

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

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
        std::reverse(u.begin(), u.end());
        std::reverse(v.begin(), v.end());
        auto intersection_basis = intersection(u, v);
        printf("%zu", intersection_basis.size());
        for (int b: intersection_basis) {
            printf(" %d", b);
        }
        puts("");
    }
}
