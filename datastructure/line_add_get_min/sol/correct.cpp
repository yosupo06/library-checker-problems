#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

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
    void add(L line) { add(line, 0, sz, 1); }
    ll query(ll x) {
        int k = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        assert(0 <= k && k < int(xs.size()) && xs[k] == x);
        k += sz;
        ll ans = 3 * TEN(18);
        while (k >= 1) {
            ans = min(ans, eval(data[k], x));
            k >>= 1;
        }
        return ans;
    }

  private:
    void add(L line, int l, int r, int k) {
        int mid = (l + r) / 2;
        ll mx = xs[mid];
        if (eval(line, mx) < eval(data[k], mx)) {
            swap(line, data[k]);
        }
        if (l + 1 == r) return;
        if (line.first > data[k].first) {
            add(line, l, mid, 2 * k);
        } else if (line.first < data[k].first) {
            add(line, mid, r, 2 * k + 1);
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    V<ll> sa(n), sb(n);
    for (int i = 0; i < n; i++) {
        cin >> sa[i] >> sb[i];
    }
    struct Q {
        int ty;
        ll a, b;
        ll p;
    };
    V<Q> query;
    V<ll> xs;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            // add
            ll a, b;
            cin >> a >> b;
            query.push_back(Q{t, a, b, -1});
        } else {
            ll p;
            cin >> p;
            xs.push_back(p);
            query.push_back(Q{t, -1, -1, p});
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    auto tr = LiChaoTree(xs);
    for (int i = 0; i < n; i++) {
        tr.add({sa[i], sb[i]});
    }

    for (auto qu : query) {
        if (qu.ty == 0) {
            // add
            tr.add({qu.a, qu.b});
        } else {
            cout << tr.query(qu.p) << "\n";
        }
    }
    return 0;
}
