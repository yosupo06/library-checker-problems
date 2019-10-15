#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

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

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    struct E {
        int x, y, ty, freq;
        ll w;
    };
    V<E> evs;
    V<int> yv;
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        evs.push_back({x, y, -1, 0, w}); // add point
        yv.push_back(y);
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        evs.push_back({l, d, i, 1, 0});
        evs.push_back({l, u, i, -1, 0});
        evs.push_back({r, d, i, -1, 0});
        evs.push_back({r, u, i, 1, 0});
        yv.push_back(d);
        yv.push_back(u);
    }
    sort(evs.begin(), evs.end(), [&](E l, E r) {
        if (l.x != r.x) return l.x < r.x;
        return l.ty > r.ty;
    });
    sort(yv.begin(), yv.end());
    yv.erase(unique(yv.begin(), yv.end()), yv.end());

    int m = int(yv.size());
    Fenwick<ll> fw(m);
    V<ll> res(q);
    for (auto e: evs) {
        int yi = int(lower_bound(yv.begin(), yv.end(), e.y) - yv.begin());
        if (e.ty == -1) {
            fw.add(yi, e.w);
        } else {
            res[e.ty] += e.freq * fw.sum(0, yi);
        }
    }

    for (auto x: res) cout << x << "\n";
    return 0;
}
