#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

template <class D, class OP> struct SparseTable {
    D e;
    OP op;
    VV<D> data;
    SparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {
        int n = int(v.size());
        if (n == 0) return;
        int lg = bsr(uint(n)) + 1;
        data = VV<D>(lg);
        data[0] = v;
        int l = 1;
        for (int s = 1; s < lg; s++) {
            data[s] = V<D>(n);
            for (int i = 0; i < n - l; i++) {
                data[s][i] = op(data[s - 1][i], data[s - 1][i + l]);
            }
            l <<= 1;
        }
    }
    D query(int l, int r) const {
        assert(l <= r);
        if (l == r) return e;
        int u = bsr(uint(r - l));
        return op(data[u][l], data[u][r - (1 << u)]);
    }
};
template <class D, class OP>
SparseTable<D, OP> get_sparse_table(V<D> v, D e, OP op) {
    return SparseTable<D, OP>(v, e, op);
}

int main() {


    int n, q;
    scanf("%d %d", &n, &q);
    V<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    auto sparse_table = get_sparse_table(a, int(TEN(9)), [&](int a, int b){ return min(a, b); });
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        cout << sparse_table.query(a, b) << "\n";
    }
    return 0;
}
