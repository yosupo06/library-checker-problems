#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <algorithm>

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

struct E {
    int u, v;
    ll dist;
};

int main() {

    int n;
    cin >> n;
    assert(n <= 1000);
    V<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<E> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({i, j, abs(x[i] - x[j]) + abs(y[i] - y[j])});
        }
    }
    sort(edges.begin(), edges.end(), [&](E a, E b) { return a.dist < b.dist; });

    ll sm = 0;
    V<E> tr;
    auto uf = UnionFind(n);    
    for (auto e: edges) {
        if (uf.same(e.u, e.v)) continue;
        uf.merge(e.u, e.v); 
        tr.push_back(e);
        sm += e.dist;        
    }

    cout << sm << "\n";
    for (auto e: tr) {
        cout << e.u << " " << e.v << "\n";
    }
    return 0;
}
