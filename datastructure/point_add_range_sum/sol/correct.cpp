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
    int n, q;
    scanf("%d %d", &n, &q);
    Fenwick<ll> fw(n);
    for (int i = 0; i < n; i++) {
        ll a;
        scanf("%lld", &a);
        fw.add(i, a);
    }
    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            //add
            int p;
            ll x;
            scanf("%d %lld", &p, &x);
            fw.add(p, x);
        } else {
            ll l, r;
            scanf("%lld %lld", &l, &r);
            cout << fw.sum(l, r) << "\n";
        }
    }
    return 0;
}
