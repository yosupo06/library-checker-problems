#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <algorithm>

using namespace std;
using ll = long long;

#define all(x) x.begin(), x.end()

template <typename X>
struct Group_Add {
  using value_type = X;
  static constexpr X op(const X &x, const X &y) noexcept { return x + y; }
  static constexpr X inverse(const X &x) noexcept { return -x; }
  static constexpr X power(const X &x, ll n) noexcept { return X(n) * x; }
  static constexpr X unit() { return X(0); }
  static constexpr bool commute = true;
};

template <typename AbelGroup>
struct FenwickTree {
  using E = typename AbelGroup::value_type;
  int n;
  vector<E> dat;
  E total;

  FenwickTree() : FenwickTree(0) {}
  FenwickTree(int n) : n(n), total(AbelGroup::unit()) {
    assert(AbelGroup::commute);
    dat.assign(n, AbelGroup::unit());
  }
  FenwickTree(vector<E> v) : n(len(v)), total(AbelGroup::unit()) {
    assert(AbelGroup::commute);
    for (int i = 0; i < n; ++i) total = AbelGroup::op(total, v[i]);
    dat = v;
    for (int i = n; i >= 1; --i) {
      int j = i + (i & -i);
      if (j <= n) dat[j - 1] = AbelGroup::op(dat[i - 1], dat[j - 1]);
    }
  }

  void reset() {
    total = AbelGroup::unit();
    dat.assign(n, AbelGroup::unit());
  }

  E sum(int k) {
    E ret = AbelGroup::unit();
    for (; k > 0; k -= k & -k) ret = AbelGroup::op(ret, dat[k - 1]);
    return ret;
  }

  E sum(int L, int R) {
    E pos = AbelGroup::unit();
    while (L < R) {
      pos = AbelGroup::op(pos, dat[R - 1]);
      R -= R & -R;
    }
    E neg = AbelGroup::unit();
    while (R < L) {
      neg = AbelGroup::op(neg, dat[L - 1]);
      L -= L & -L;
    }
    return AbelGroup::op(pos, AbelGroup::inverse(neg));
  }

  E sum_all() { return total; }

  void add(int k, E x) {
    total = AbelGroup::op(total, x);
    for (++k; k <= n; k += k & -k) dat[k - 1] = AbelGroup::op(dat[k - 1], x);
  }

  template <class F>
  int max_right(F &check) {
    assert(check(E(0)));
    ll i = 0;
    E s = AbelGroup::unit();
    int k = 1;
    int N = dat.size() + 1;
    while (2 * k < N) k *= 2;
    while (k) {
      if (i + k < N && check(AbelGroup::op(s, dat[i + k - 1]))) {
        i += k;
        s = AbelGroup::op(s, dat[i - 1]);
      }
      k >>= 1;
    }
    return i;
  }

  int find_kth(E k) {
    auto check = [&](E x) -> bool { return x <= k; };
    return max_right(check);
  }

  // void debug() { print("fenwick", dat); }
};

template <typename AbelGroup, bool SMALL = false>
struct Point_Add_Rectangle_Sum {
  using G = typename AbelGroup::value_type;
  int Q;
  vector<ll> X, Y;
  vector<G> WT;
  vector<tuple<ll, ll, ll, ll>> rect;

  Point_Add_Rectangle_Sum() {}

  void add_query(ll x, ll y, G w) {
    X.emplace_back(x), Y.emplace_back(y), WT.emplace_back(w);
  }

  void sum_query(ll xl, ll yl, ll xr, ll yr) {
    rect.emplace_back(xl, yl, xr, yr);
  }

  vector<G> calc() {
    int N = X.size(), Q = rect.size();
    if (N == 0) return vector<G>(Q, AbelGroup::unit());
    int NX = 0, NY = 0;
    if (!SMALL) {
      vector<ll> keyX = X, keyY = Y;
      sort(all(keyX));
      keyX.erase(unique(all(keyX)), keyX.end());
      sort(all(keyY));
      keyY.erase(unique(all(keyY)), keyY.end());
      NX = keyX.size(), NY = keyY.size();
      for (auto &&x: X) x = lower_bound(all(keyX), x) - keyX.begin();
      for (auto &&y: Y) y = lower_bound(all(keyY), y) - keyY.begin();
      for (auto &&[xl, yl, xr, yr]: rect) {
        xl = lower_bound(all(keyX), xl) - keyX.begin();
        xr = lower_bound(all(keyX), xr) - keyX.begin();
        yl = lower_bound(all(keyY), yl) - keyY.begin();
        yr = lower_bound(all(keyY), yr) - keyY.begin();
      }
    }
    if (SMALL) {
      ll mx = *(min_element(X.begin(), X.end()));
      ll my = *(min_element(Y.begin(), Y.end()));
      for (auto &&x: X) x -= mx;
      for (auto &&y: Y) y -= my;
      NX = *(max_element(X.begin(), X.end())) + 1;
      NY = *(max_element(Y.begin(), Y.end())) + 1;
      for (auto &&[xl, yl, xr, yr]: rect) {
        xl -= mx, xr -= mx;
        yl -= my, yr -= my;
        xl = max(0, min<int>(xl, NX));
        xr = max(0, min<int>(xr, NX));
        yl = max(0, min<int>(yl, NY));
        yr = max(0, min<int>(yr, NY));
      }
    }
    vector<vector<pair<int, G>>> ADD(NY + 1);
    vector<vector<tuple<int, int, int>>> CALC_1(NY + 1);
    vector<vector<tuple<int, int, int>>> CALC_2(NY + 1);
    for (int n = 0; n < N; ++n) { ADD[Y[n]].emplace_back(X[n], WT[n]); }
    for (int q = 0; q < Q; ++q) {
      auto &[xl, yl, xr, yr] = rect[q];
      CALC_1[yr].emplace_back(xl, xr, q);
      CALC_2[yl].emplace_back(xl, xr, q);
    };

    vector<G> res(Q, AbelGroup::unit());
    FenwickTree<AbelGroup> bit(NX);

    for (int y = 0; y <= NY; ++y) {
      for (auto &&[xl, xr, q]: CALC_1[y]) {
        auto x = bit.sum(xl, xr);
        res[q] = AbelGroup::op(res[q], x);
      }
      for (auto &&[xl, xr, q]: CALC_2[y]) {
        auto x = AbelGroup::inverse(bit.sum(xl, xr));
        res[q] = AbelGroup::op(res[q], x);
      }
      for (auto &&[x, g]: ADD[y]) { bit.add(x, g); }
    }
    return res;
  }
};

template <typename AbelGroup, bool SMALL = false>
struct Rectangle_Add_Rectangle_Sum {
  using WT = typename AbelGroup::value_type;
  using WT4 = tuple<WT, WT, WT, WT>;

  struct G {
    using X = WT4;
    using value_type = X;
    static X op(const X &x, const X &y) {
      auto &[ax, bx, cx, dx] = x;
      auto &[ay, by, cy, dy] = y;
      return {AbelGroup::op(ax, ay), AbelGroup::op(bx, by),
              AbelGroup::op(cx, cy), AbelGroup::op(dx, dy)};
    }
    static X inverse(const X &x) {
      auto &[ax, bx, cx, dx] = x;
      return {AbelGroup::inverse(ax), AbelGroup::inverse(bx),
              AbelGroup::inverse(cx), AbelGroup::inverse(dx)};
    }
    static X power(const X &x, ll n) {
      auto &[ax, bx, cx, dx] = x;
      return {AbelGroup::power(ax, n), AbelGroup::power(bx, n),
              AbelGroup::power(cx, n), AbelGroup::power(dx, n)};
    }
    static constexpr X unit() {
      auto u = AbelGroup::unit();
      return {u, u, u, u};
    }
    static constexpr bool commute = true;
  };

  vector<tuple<ll, ll, ll, ll>> query;
  Point_Add_Rectangle_Sum<G, SMALL> X;
  ll min_x = 0, min_y = 0;

  void add_query(ll xl, ll yl, ll xr, ll yr, WT w) {
    assert(xl <= xr && yl <= yr);
    min_x = min(min_x, xl);
    min_y = min(min_y, yl);
    // (xl,yl) に (x-xl)(y-yl) を加算
    auto nw = AbelGroup::inverse(w);
    X.add_query(xl, yl,
                {w, AbelGroup::power(w, -yl), AbelGroup::power(w, -xl),
                 AbelGroup::power(w, +xl * yl)});
    // (xl,yr) に (x-xl)(y-yr) を減算
    X.add_query(xl, yr,
                {nw, AbelGroup::power(w, +yr), AbelGroup::power(w, +xl),
                 AbelGroup::power(w, -xl * yr)});
    // (xr,yl) に (x-xr)(y-yl) を減算
    X.add_query(xr, yl,
                {nw, AbelGroup::power(w, +yl), AbelGroup::power(w, +xr),
                 AbelGroup::power(w, -xr * yl)});
    // (xr,yr) に (x-xr)(y-yr) を加算
    X.add_query(xr, yr,
                {w, AbelGroup::power(w, -yr), AbelGroup::power(w, -xr),
                 AbelGroup::power(w, +xr * yr)});
  }

  void sum_query(ll xl, ll yl, ll xr, ll yr) {
    assert(xl <= xr && yl <= yr);
    query.emplace_back(xl, yl, xr, yr);
    X.sum_query(min_x, min_y, xl, yl);
    X.sum_query(min_x, min_y, xl, yr);
    X.sum_query(min_x, min_y, xr, yl);
    X.sum_query(min_x, min_y, xr, yr);
  }

  vector<WT> calc() {
    ll Q = query.size();
    vector<WT> ANS(Q);
    auto tmp = X.calc();

    for (int q = 0; q < Q; ++q) {
      auto [xl, yl, xr, yr] = query[q];
      WT p = AbelGroup::unit(), m = AbelGroup::unit();
      {
        auto [a, b, c, d] = tmp[4 * q + 0];
        p = AbelGroup::op(p, AbelGroup::power(a, xl * yl));
        p = AbelGroup::op(p, AbelGroup::power(b, xl));
        p = AbelGroup::op(p, AbelGroup::power(c, yl));
        p = AbelGroup::op(p, d);
      }
      {
        auto [a, b, c, d] = tmp[4 * q + 1];
        m = AbelGroup::op(m, AbelGroup::power(a, xl * yr));
        m = AbelGroup::op(m, AbelGroup::power(b, xl));
        m = AbelGroup::op(m, AbelGroup::power(c, yr));
        m = AbelGroup::op(m, d);
      }
      {
        auto [a, b, c, d] = tmp[4 * q + 2];
        m = AbelGroup::op(m, AbelGroup::power(a, xr * yl));
        m = AbelGroup::op(m, AbelGroup::power(b, xr));
        m = AbelGroup::op(m, AbelGroup::power(c, yl));
        m = AbelGroup::op(m, d);
      }
      {
        auto [a, b, c, d] = tmp[4 * q + 3];
        p = AbelGroup::op(p, AbelGroup::power(a, xr * yr));
        p = AbelGroup::op(p, AbelGroup::power(b, xr));
        p = AbelGroup::op(p, AbelGroup::power(c, yr));
        p = AbelGroup::op(p, d);
      }
      ANS[q] = AbelGroup::op(p, AbelGroup::inverse(m));
    }
    return ANS;
  }
};

template <unsigned int mod>
struct modint {
  static constexpr bool is_modint = true;
  unsigned int val;
  constexpr modint(const ll val = 0) noexcept
      : val(val >= 0 ? val % mod : (mod - (-val) % mod) % mod) {}
  bool operator<(const modint &other) const {
    return val < other.val;
  } // To use std::map
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= mod) val -= mod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += mod - p.val) >= mod) val -= mod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = (unsigned int)(1LL * val * p.val % mod);
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint(get_mod() - val); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  modint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(int64_t n) const {
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr unsigned int get_mod() { return mod; }
};

using mint = modint<998244353>;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  Rectangle_Add_Rectangle_Sum<Group_Add<mint>, 0> X;

  for (int n = 0; n < N; ++n) {
    ll l, d, r, u, w;
    scanf("%lld %lld %lld %lld %lld", &l, &d, &r, &u, &w);
    X.add_query(l, d, r, u, mint(w));
  }

  for (int q = 0; q < Q; ++q) {
    ll l, d, r, u;
    scanf("%lld %lld %lld %lld", &l, &d, &r, &u);
    X.sum_query(l, d, r, u);
  }

  auto ANS = X.calc();
  for (auto &&x: ANS) printf("%d\n", x.val);
  return 0;
}