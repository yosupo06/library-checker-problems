#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

constexpr ll INF = 3 * TEN(18);
struct LiChaoTree {
    using L = pair<ll, ll>;  // l.first * x + l.second
    int sz;
    V<L> data;
    V<ll> xs;
    static ll eval(L l, ll x) { return l.first * x + l.second; }
    LiChaoTree(V<ll> _xs) : xs(_xs) {
        int n = int(xs.size());
        int lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        while (int(xs.size()) < sz) xs.push_back(TEN(9));
        data = V<L>(2 * sz, L(0, 3 * TEN(18)));
    }
    void add(L line, int l, int r) {
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        add(line, l, r, 0, sz, 1);
    }
    ll query(ll x) {
        int k = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        assert(0 <= k && k < int(xs.size()) && xs[k] == x);
        k += sz;
        ll ans = INF;
        while (k >= 1) {
            ans = min(ans, eval(data[k], x));
            k >>= 1;
        }
        return ans;
    }

  private:
    void add(L line, int ql, int qr, int l, int r, int k) {
        if (qr <= l || r <= ql) {
            return;
        } else if (ql <= l && r <= qr) {
            int mid = (l + r) / 2;
            ll mx = xs[mid];
            if (eval(line, mx) < eval(data[k], mx)) {
                swap(line, data[k]);
            }
            if (l + 1 == r) return;
            if (line.first > data[k].first) {
                add(line, ql, qr, l, mid, 2 * k);
            } else if (line.first < data[k].first) {
                add(line, ql, qr, mid, r, 2 * k + 1);
            }
        } else {
            int mid = (l + r) / 2;
            add(line, ql, qr, l, mid, 2 * k);
            add(line, ql, qr, mid, r, 2 * k + 1);
        }
    }
};

int main() {

    int n, q;
    scanf("%d %d", &n, &q);
    V<ll> sl(n), sr(n), sa(n), sb(n);
    V<ll> xs;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &sl[i], &sr[i], &sa[i], &sb[i]);
        xs.push_back(sl[i]);
        xs.push_back(sr[i]);
    }
    struct Q {
        int ty;
        ll l, r, a, b;
        ll p;
    };
    V<Q> query;
    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            // add
            ll l, r, a, b;
            scanf("%lld %lld %lld %lld", &l, &r, &a, &b);
            xs.push_back(l);
            xs.push_back(r);
            query.push_back(Q{t, l, r, a, b, -1});
        } else {
            ll p;
            scanf("%lld", &p);
            xs.push_back(p);
            query.push_back(Q{t, -1, -1, -1, -1, p});
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    auto tr = LiChaoTree(xs);
    for (int i = 0; i < n; i++) {
        tr.add({sa[i], sb[i]}, sl[i], sr[i]);
    }

    for (auto qu : query) {
        if (qu.ty == 0) {
            // add
            tr.add({qu.a, qu.b}, qu.l, qu.r);
        } else {
            ll ans = tr.query(qu.p);
            cout << (ans == INF ? "INFINITY" : to_string(ans)) << "\n";
        }
    }
    return 0;
}
