#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

template <class T> struct Fenwick {
    int n;
    V<T> seg;
    Fenwick(int _n = 0) : n(_n), seg(n + 1) {}
    /// i番目の要素にxを追加する
    void add(int i, T x) {
        i++;
        while (i <= n) {
            seg[i] += x;
            i += i & -i;
        }
    }
    /// [0, i)のsum
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }
    /// [a, b)のsum
    T sum(int a, int b) { return sum(b) - sum(a); }
};

VV<int> g;
V<int> lord, rord;
int ord_c;

void dfs(int u) {
    lord[u] = ord_c++;
    for (int v: g[u]) {
        dfs(v);
    }
    rord[u] = ord_c;
}


int main() {
    
    int n, q;
    scanf("%d %d", &n, &q);
    g = VV<int>(n);

    V<ll> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        g[p].push_back(i);
    }
    lord = V<int>(n);
    rord = V<int>(n);

    dfs(0);

    auto fw = Fenwick<ll>(n);

    for (int i = 0; i < n; i++) {
        fw.add(lord[i], a[i]);
    }

    for (int i = 0; i < q; i++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int u; ll x;
            scanf("%d %lld", &u, &x);
            fw.add(lord[u], x);
        } else {
            int u;
            scanf("%d", &u);
            cout << fw.sum(lord[u], rord[u]) << "\n";
        }
    }
    return 0;
}
