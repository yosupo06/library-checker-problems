#include <vector>
#include <iostream>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct UnionFind {
    V<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

int main() {


    int n, q;
    scanf("%d %d", &n, &q);
    UnionFind uf(n);
    for (int i = 0; i < q; i++) {
        int ty, a, b;
        scanf("%d %d %d", &ty, &a, &b);
        if (ty == 0) {
            uf.merge(a, b);
        } else {
            printf("%d\n", int(uf.same(a, b)));
        }
    }
    return 0;
}
