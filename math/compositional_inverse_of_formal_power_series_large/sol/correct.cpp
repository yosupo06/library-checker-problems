#include <cstdio>
#include <vector>
#include <cassert>
#include <array>
#include <algorithm>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

using pi = pair<ll, ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}

template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (len(dat) <= n) {
    int k = len(dat);
    int q = (mod + k - 1) / k;
    dat.eb(dat[k * q - mod] * mint::raw(q));
  }
  return dat[n];
}

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * mint::raw(len(dat)));
  return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
  static vector<mint> dat = {1, 1};
  if (n < 0) return mint(0);
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * inv<mint>(len(dat)));
  return dat[n];
}

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  static modint raw(u32 v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(u32 x) : val(x % umod) {}
  constexpr modint(u64 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint& other) const { return val < other.val; }
  modint& operator+=(const modint& p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator-=(const modint& p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator*=(const modint& p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint& operator/=(const modint& p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint& p) const { return modint(*this) += p; }
  modint operator-(const modint& p) const { return modint(*this) -= p; }
  modint operator*(const modint& p) const { return modint(*this) *= p; }
  modint operator/(const modint& p) const { return modint(*this) /= p; }
  bool operator==(const modint& p) const { return val == p.val; }
  bool operator!=(const modint& p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
  // (n, r), r は 1 の 2^n 乗根
  static constexpr pair<int, int> ntt_info() {
    if (mod == 998244353) return {23, 31};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

using modint998 = modint<998244353>;

template <typename mint>
vc<mint> differentiate(const vc<mint>& f) {
  if (len(f) <= 1) return {};
  vc<mint> g(len(f) - 1);
  FOR(i, len(g)) g[i] = f[i + 1] * mint(i + 1);
  return g;
}

template <class T>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vc<T> ans(n + m - 1);
  if (n <= 16 && (T::get_mod() < (1 << 30))) {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u64 sm = 0;
      for (int i = s; i < t; ++i) { sm += u64(a[i].val) * (b[k - i].val); }
      ans[k] = sm;
    }
  } else {
    FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  }
  return ans;
}

// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T>& f, const vc<T>& g) {
  const int thresh = 30;
  if (min(len(f), len(g)) <= thresh) return convolution_naive(f, g);
  int n = max(len(f), len(g));
  int m = ceil(n, 2);
  vc<T> f1, f2, g1, g2;
  if (len(f) < m) f1 = f;
  if (len(f) >= m) f1 = {f.begin(), f.begin() + m};
  if (len(f) >= m) f2 = {f.begin() + m, f.end()};
  if (len(g) < m) g1 = g;
  if (len(g) >= m) g1 = {g.begin(), g.begin() + m};
  if (len(g) >= m) g2 = {g.begin() + m, g.end()};
  vc<T> a = convolution_karatsuba(f1, g1);
  vc<T> b = convolution_karatsuba(f2, g2);
  FOR(i, len(f2)) f1[i] += f2[i];
  FOR(i, len(g2)) g1[i] += g2[i];
  vc<T> c = convolution_karatsuba(f1, g1);
  vc<T> F(len(f) + len(g) - 1);
  assert(2 * m + len(b) <= len(F));
  FOR(i, len(a)) F[i] += a[i], c[i] -= a[i];
  FOR(i, len(b)) F[2 * m + i] += b[i], c[i] -= b[i];
  if (c.back() == T(0)) c.pop_back();
  FOR(i, len(c)) if (c[i] != T(0)) F[m + i] += c[i];
  return F;
}

template <class mint>
void ntt(vector<mint>& a, bool inverse) {
  assert(mint::can_ntt());
  const int rank2 = mint::ntt_info().fi;
  const int mod = mint::get_mod();
  static array<mint, 30> root, iroot;
  static array<mint, 30> rate2, irate2;
  static array<mint, 30> rate3, irate3;

  assert(rank2 != -1 && len(a) <= (1 << max(0, rank2)));

  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    root[rank2] = mint::ntt_info().se;
    iroot[rank2] = mint(1) / root[rank2];
    FOR_R(i, rank2) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    mint prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 2; i++) {
      rate2[i] = root[i + 2] * prod;
      irate2[i] = iroot[i + 2] * iprod;
      prod *= iroot[i + 2];
      iprod *= root[i + 2];
    }
    prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 3; i++) {
      rate3[i] = root[i + 3] * prod;
      irate3[i] = iroot[i + 3] * iprod;
      prod *= iroot[i + 3];
      iprod *= root[i + 3];
    }
  }

  int n = int(a.size());
  int h = topbit(n);
  assert(n == 1 << h);
  if (!inverse) {
    int len = 0;
    while (len < h) {
      if (h - len == 1) {
        int p = 1 << (h - len - 1);
        mint rot = 1;
        FOR(s, 1 << len) {
          int offset = s << (h - len);
          FOR(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * rot;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          rot *= rate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = root[2];
        for (int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            u64 mod2 = u64(mod) * mod;
            u64 a0 = a[i + offset].val;
            u64 a1 = u64(a[i + offset + p].val) * rot.val;
            u64 a2 = u64(a[i + offset + 2 * p].val) * rot2.val;
            u64 a3 = u64(a[i + offset + 3 * p].val) * rot3.val;
            u64 a1na3imag = (a1 + mod2 - a3) % mod * imag.val;
            u64 na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          rot *= rate3[topbit(~s & -~s)];
        }
        len += 2;
      }
    }
  } else {
    mint coef = mint(1) / mint(len(a));
    FOR(i, len(a)) a[i] *= coef;
    int len = h;
    while (len) {
      if (len == 1) {
        int p = 1 << (h - len);
        mint irot = 1;
        FOR(s, 1 << (len - 1)) {
          int offset = s << (h - len + 1);
          FOR(i, p) {
            u64 l = a[i + offset].val;
            u64 r = a[i + offset + p].val;
            a[i + offset] = l + r;
            a[i + offset + p] = (mod + l - r) * irot.val;
          }
          irot *= irate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint irot = 1, iimag = iroot[2];
        FOR(s, (1 << (len - 2))) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for (int i = 0; i < p; i++) {
            u64 a0 = a[i + offset + 0 * p].val;
            u64 a1 = a[i + offset + 1 * p].val;
            u64 a2 = a[i + offset + 2 * p].val;
            u64 a3 = a[i + offset + 3 * p].val;
            u64 x = (mod + a2 - a3) * iimag.val % mod;
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] = (a0 + mod - a1 + x) * irot.val;
            a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * irot2.val;
            a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * irot3.val;
          }
          irot *= irate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  }
}

template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
  if (a.empty() || b.empty()) return {};
  int n = int(a.size()), m = int(b.size());
  int sz = 1;
  while (sz < n + m - 1) sz *= 2;

  // sz = 2^k のときの高速化。分割統治的なやつで損しまくるので。
  if ((n + m - 3) <= sz / 2) {
    auto a_last = a.back(), b_last = b.back();
    a.pop_back(), b.pop_back();
    auto c = convolution(a, b);
    c.resize(n + m - 1);
    c[n + m - 2] = a_last * b_last;
    FOR(i, len(a)) c[i + len(b)] += a[i] * b_last;
    FOR(i, len(b)) c[i + len(a)] += b[i] * a_last;
    return c;
  }

  a.resize(sz), b.resize(sz);
  bool same = a == b;
  ntt(a, 0);
  if (same) {
    b = a;
  } else {
    ntt(b, 0);
  }
  FOR(i, sz) a[i] *= b[i];
  ntt(a, 1);
  a.resize(n + m - 1);
  return a;
}

template <typename mint>
vc<mint> convolution(const vc<mint>& a, const vc<mint>& b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
  return convolution_ntt(a, b);
}

template <typename T>
vc<vc<T>> convolution2d(vc<vc<T>>& f, vc<vc<T>>& g) {
  auto shape = [&](vc<vc<T>>& f) -> pi {
    ll H = len(f);
    ll W = (H == 0 ? 0 : len(f[0]));
    return {H, W};
  };
  auto [H1, W1] = shape(f);
  auto [H2, W2] = shape(g);
  ll H = H1 + H2 - 1;
  ll W = W1 + W2 - 1;

  vc<T> ff(H1 * W);
  vc<T> gg(H2 * W);
  FOR(x, H1) FOR(y, W1) ff[W * x + y] = f[x][y];
  FOR(x, H2) FOR(y, W2) gg[W * x + y] = g[x][y];
  auto hh = convolution(ff, gg);
  vc<vc<T>> h(H, vc<T>(W));
  FOR(x, H) FOR(y, W) h[x][y] = hh[W * x + y];
  return h;
}

// a^0, ..., a^N
template <typename mint>
vc<mint> powertable_1(mint a, ll N) {
  // table of a^i
  vc<mint> f(N + 1, 1);
  FOR(i, N) f[i + 1] = a * f[i];
  return f;
}

// f(x) -> f(x+c)
template <typename mint>
vc<mint> poly_taylor_shift(vc<mint> f, mint c) {
  ll N = len(f);
  FOR(i, N) f[i] *= fact<mint>(i);
  auto b = powertable_1<mint>(c, N);
  FOR(i, N) b[i] *= fact_inv<mint>(i);
  reverse(all(f));
  f = convolution(f, b);
  f.resize(N);
  reverse(all(f));
  FOR(i, N) f[i] *= fact_inv<mint>(i);
  return f;
}

// n, m 次多項式 (n>=m) a, b → n-m 次多項式 c
// c[i] = sum_j b[j]a[i+j]
template <typename mint>
vc<mint> middle_product(vc<mint>& a, vc<mint>& b) {
  assert(len(a) >= len(b));
  if (b.empty()) return vc<mint>(len(a) - len(b) + 1);
  if (min(len(b), len(a) - len(b) + 1) <= 60) {
    return middle_product_naive(a, b);
  }
  int n = 1 << __lg(2 * len(a) - 1);
  vc<mint> fa(n), fb(n);
  copy(a.begin(), a.end(), fa.begin());
  copy(b.rbegin(), b.rend(), fb.begin());
  ntt(fa, 0), ntt(fb, 0);
  FOR(i, n) fa[i] *= fb[i];
  ntt(fa, 1);
  fa.resize(len(a));
  fa.erase(fa.begin(), fa.begin() + len(b) - 1);
  return fa;
}

template <typename mint>
vc<mint> middle_product_naive(vc<mint>& a, vc<mint>& b) {
  vc<mint> res(len(a) - len(b) + 1);
  FOR(i, len(res)) FOR(j, len(b)) res[i] += b[j] * a[i + j];
  return res;
}

template <typename mint>
int count_terms(const vc<mint>& f) {
  int t = 0;
  FOR(i, len(f)) if (f[i] != mint(0))++ t;
  return t;
}

template <typename mint>
vc<mint> fps_inv_sparse(const vc<mint>& f) {
  int N = len(f);
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> g(N);
  mint g0 = mint(1) / f[0];
  g[0] = g0;
  FOR(n, 1, N) {
    mint rhs = 0;
    for (auto&& [k, fk]: dat) {
      if (k > n) break;
      rhs -= fk * g[n - k];
    }
    g[n] = rhs * g0;
  }
  return g;
}

template <typename mint>
vc<mint> fps_inv_dense_ntt(const vc<mint>& F) {
  vc<mint> G = {mint(1) / F[0]};
  ll N = len(F), n = 1;
  G.reserve(N);
  while (n < N) {
    vc<mint> f(2 * n), g(2 * n);
    FOR(i, min(N, 2 * n)) f[i] = F[i];
    FOR(i, n) g[i] = G[i];
    ntt(f, false), ntt(g, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n) f[i] = 0;
    ntt(f, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n, min(N, 2 * n)) G.eb(-f[i]);
    n *= 2;
  }
  return G;
}

template <typename mint>
vc<mint> fps_inv_dense(const vc<mint>& F) {
  return fps_inv_dense_ntt(F);
}

template <typename mint>
vc<mint> fps_inv(const vc<mint>& f) {
  assert(f[0] != mint(0));
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 160 : 820);
  return (n <= t ? fps_inv_sparse<mint>(f) : fps_inv_dense<mint>(f));
}

// f/g. f の長さで出力される.
template <typename mint, bool SPARSE = false>
vc<mint> fps_div(vc<mint> f, vc<mint> g) {
  if (SPARSE || count_terms(g) < 200) return fps_div_sparse(f, g);
  int n = len(f);
  g.resize(n);
  g = fps_inv<mint>(g);
  f = convolution(f, g);
  f.resize(n);
  return f;
}

// f/g ただし g は sparse
template <typename mint>
vc<mint> fps_div_sparse(vc<mint> f, vc<mint>& g) {
  if (g[0] != mint(1)) {
    mint cf = g[0].inverse();
    for (auto&& x: f) x *= cf;
    for (auto&& x: g) x *= cf;
  }

  vc<pair<int, mint>> dat;
  FOR(i, 1, len(g)) if (g[i] != mint(0)) dat.eb(i, -g[i]);
  FOR(i, len(f)) {
    for (auto&& [j, x]: dat) {
      if (i >= j) f[i] += x * f[i - j];
    }
  }
  return f;
}

// 不定積分：integrate(f)
// 定積分：integrate(f, L, R)
template <typename mint>
vc<mint> integrate(const vc<mint>& f) {
  vc<mint> g(len(f) + 1);
  FOR3(i, 1, len(g)) g[i] = f[i - 1] * inv<mint>(i);
  return g;
}

// 不定積分：integrate(f)
// 定積分：integrate(f, L, R)
template <typename mint>
mint integrate(const vc<mint>& f, mint L, mint R) {
  mint I = 0;
  mint pow_L = 1, pow_R = 1;
  FOR(i, len(f)) {
    pow_L *= L, pow_R *= R;
    I += inv<mint>(i + 1) * f[i] * (pow_R - pow_L);
  }
  return I;
}

template <typename mint>
vc<mint> fps_exp_sparse(vc<mint>& f) {
  if (len(f) == 0) return {mint(1)};
  assert(f[0] == 0);
  int N = len(f);
  // df を持たせる
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i - 1, mint(i) * f[i]);
  vc<mint> F(N);
  F[0] = 1;
  FOR(n, 1, N) {
    mint rhs = 0;
    for (auto&& [k, fk]: dat) {
      if (k > n - 1) break;
      rhs += fk * F[n - 1 - k];
    }
    F[n] = rhs * inv<mint>(n);
  }
  return F;
}

template <typename mint>
vc<mint> fps_exp_dense(vc<mint>& h) {
  const int n = len(h);
  assert(n > 0 && h[0] == mint(0));
  if (mint::can_ntt()) {
    vc<mint>& f = h;
    vc<mint> b = {1, (1 < n ? f[1] : 0)};
    vc<mint> c = {1}, z1, z2 = {1, 1};
    while (len(b) < n) {
      int m = len(b);
      auto y = b;
      y.resize(2 * m);
      ntt(y, 0);
      z1 = z2;
      vc<mint> z(m);
      FOR(i, m) z[i] = y[i] * z1[i];
      ntt(z, 1);
      FOR(i, m / 2) z[i] = 0;
      ntt(z, 0);
      FOR(i, m) z[i] *= -z1[i];
      ntt(z, 1);
      c.insert(c.end(), z.begin() + m / 2, z.end());
      z2 = c;
      z2.resize(2 * m);
      ntt(z2, 0);

      vc<mint> x(f.begin(), f.begin() + m);
      FOR(i, len(x) - 1) x[i] = x[i + 1] * mint(i + 1);
      x.back() = 0;
      ntt(x, 0);
      FOR(i, m) x[i] *= y[i];
      ntt(x, 1);

      FOR(i, m - 1) x[i] -= b[i + 1] * mint(i + 1);

      x.resize(m + m);
      FOR(i, m - 1) x[m + i] = x[i], x[i] = 0;
      ntt(x, 0);
      FOR(i, m + m) x[i] *= z2[i];
      ntt(x, 1);
      FOR_R(i, len(x) - 1) x[i + 1] = x[i] * inv<mint>(i + 1);
      x[0] = 0;

      FOR3(i, m, min(n, m + m)) x[i] += f[i];
      FOR(i, m) x[i] = 0;
      ntt(x, 0);
      FOR(i, m + m) x[i] *= y[i];
      ntt(x, 1);
      b.insert(b.end(), x.begin() + m, x.end());
    }
    b.resize(n);
    return b;
  }

  const int L = len(h);
  assert(L > 0 && h[0] == mint(0));
  int LOG = 0;
  while (1 << LOG < L) ++LOG;
  h.resize(1 << LOG);
  auto dh = differentiate(h);
  vc<mint> f = {1}, g = {1};
  int m = 1;

  vc<mint> p;

  FOR(LOG) {
    p = convolution(f, g);
    p.resize(m);
    p = convolution(p, g);
    p.resize(m);
    g.resize(m);
    FOR(i, m) g[i] += g[i] - p[i];
    p = {dh.begin(), dh.begin() + m - 1};
    p = convolution(f, p);
    p.resize(m + m - 1);
    FOR(i, m + m - 1) p[i] = -p[i];
    FOR(i, m - 1) p[i] += mint(i + 1) * f[i + 1];
    p = convolution(p, g);

    p.resize(m + m - 1);
    FOR(i, m - 1) p[i] += dh[i];
    p = integrate(p);
    FOR(i, m + m) p[i] = h[i] - p[i];
    p[0] += mint(1);
    f = convolution(f, p);
    f.resize(m + m);
    m += m;
  }
  f.resize(L);
  return f;
}

template <typename mint>
vc<mint> fps_exp(vc<mint>& f) {
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 320 : 3000);
  return (n <= t ? fps_exp_sparse<mint>(f) : fps_exp_dense<mint>(f));
}

template <typename mint>
vc<mint> fps_log_dense(const vc<mint>& f) {
  assert(f[0] == mint(1));
  ll N = len(f);
  vc<mint> df = f;
  FOR(i, N) df[i] *= mint(i);
  df.erase(df.begin());
  auto f_inv = fps_inv(f);
  auto g = convolution(df, f_inv);
  g.resize(N - 1);
  g.insert(g.begin(), 0);
  FOR(i, N) g[i] *= inv<mint>(i);
  return g;
}

template <typename mint>
vc<mint> fps_log_sparse(const vc<mint>& f) {
  int N = f.size();
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> F(N);
  vc<mint> g(N - 1);
  for (int n = 0; n < N - 1; ++n) {
    mint rhs = mint(n + 1) * f[n + 1];
    for (auto&& [i, fi]: dat) {
      if (i > n) break;
      rhs -= fi * g[n - i];
    }
    g[n] = rhs;
    F[n + 1] = rhs * inv<mint>(n + 1);
  }
  return F;
}

template <typename mint>
vc<mint> fps_log(const vc<mint>& f) {
  assert(f[0] == mint(1));
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 200 : 1200);
  return (n <= t ? fps_log_sparse<mint>(f) : fps_log_dense<mint>(f));
}

// fps の k 乗を求める。k >= 0 の前提である。
// 定数項が 1 で、k が mint の場合には、fps_pow_1 を使うこと。
// ・dense な場合： log, exp を使う O(NlogN)
// ・sparse な場合： O(NK)
template <typename mint>
vc<mint> fps_pow(const vc<mint>& f, ll k) {
  assert(0 <= k);
  int n = len(f);
  if (k == 0) {
    vc<mint> g(n);
    g[0] = mint(1);
    return g;
  }
  int d = n;
  FOR_R(i, n) if (f[i] != 0) d = i;
  // d * k >= n
  if (d >= ceil<ll>(n, k)) {
    vc<mint> g(n);
    return g;
  }
  ll off = d * k;
  mint c = f[d];
  mint c_inv = mint(1) / mint(c);
  vc<mint> g(n - off);
  FOR(i, n - off) g[i] = f[d + i] * c_inv;
  g = fps_pow_1(g, mint(k));
  vc<mint> h(n);
  c = c.pow(k);
  FOR(i, len(g)) h[off + i] = g[i] * c;
  return h;
}

template <typename mint>
vc<mint> fps_pow_1_sparse(const vc<mint>& f, mint K) {
  int N = len(f);
  assert(N == 0 || f[0] == mint(1));
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> g(N);
  g[0] = 1;
  FOR(n, N - 1) {
    mint& x = g[n + 1];
    for (auto&& [d, cf]: dat) {
      if (d > n + 1) break;
      mint t = cf * g[n - d + 1];
      x += t * (K * mint(d) - mint(n - d + 1));
    }
    x *= inv<mint>(n + 1);
  }
  return g;
}

template <typename mint>
vc<mint> fps_pow_1_dense(const vc<mint>& f, mint K) {
  assert(f[0] == mint(1));
  auto log_f = fps_log(f);
  FOR(i, len(f)) log_f[i] *= K;
  return fps_exp_dense(log_f);
}

template <typename mint>
vc<mint> fps_pow_1(const vc<mint>& f, mint K) {
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 100 : 1300);
  return (n <= t ? fps_pow_1_sparse(f, K) : fps_pow_1_dense(f, K));
}

// f^e, sparse, O(NMK)
template <typename mint>
vvc<mint> fps_pow_1_sparse_2d(vvc<mint> f, mint n) {
  assert(f[0][0] == mint(1));
  int N = len(f), M = len(f[0]);
  vv(mint, dp, N, M);
  dp[0] = fps_pow_1_sparse<mint>(f[0], n);

  vc<tuple<int, int, mint>> dat;
  FOR(i, N) FOR(j, M) {
    if ((i > 0 || j > 0) && f[i][j] != mint(0)) dat.eb(i, j, f[i][j]);
  }
  FOR(i, 1, N) {
    FOR(j, M) {
      // F = f^n, f dF = n df F
      // [x^{i-1}y^j]
      mint lhs = 0, rhs = 0;
      for (auto&& [a, b, c]: dat) {
        if (a < i && b <= j) lhs += dp[i - a][j - b] * mint(i - a);
        if (a <= i && b <= j) rhs += dp[i - a][j - b] * c * mint(a);
      }
      dp[i][j] = (n * rhs - lhs) * inv<mint>(i);
    }
  }
  return dp;
}

// https://noshi91.hatenablog.com/entry/2024/03/16/224034
// k を固定して [x^k]f(x)^ig(x) を i=0,1,...,n で求める.
template <typename mint>
vc<mint> coef_of_fps_pows(vc<mint> f, int k, int n, vc<mint> g = {mint(1)}) {
  assert(len(f) == k + 1);
  vv(mint, P, k + 1, 2);
  vv(mint, Q, k + 1, 2);
  Q[0][0] = 1;
  FOR(i, len(g)) if (i <= k) P[i][0] = g[i];
  FOR(i, len(f)) if (i <= k) Q[i][1] = -f[i];
  FOR(i, len(f)) Q[i][1] = -f[i];

  while (k > 0) {
    int H = len(P), W = len(P[0]);
    vvc<mint> R = Q;
    FOR(i, H) {
      if (i % 2 == 0) continue;
      FOR(j, W) { R[i][j] = -R[i][j]; }
    }
    vvc<mint> F = convolution2d<mint>(P, R);
    vvc<mint> G = convolution2d<mint>(Q, R);
    P.resize(k / 2 + 1);
    Q.resize(k / 2 + 1);
    FOR(i, len(P)) P[i] = F[2 * i | (k & 1)];
    FOR(i, len(Q)) Q[i] = G[2 * i];
    k /= 2;
    FOR(i, len(P)) if (len(P[i]) > n + 1) P[i].resize(n + 1);
    FOR(i, len(Q)) if (len(Q[i]) > n + 1) Q[i].resize(n + 1);
  }
  vc<mint> F = P[0], G = Q[0];
  F.resize(n + 1), G.resize(n + 1);
  return fps_div<mint>(F, G);
}

// https://noshi91.hatenablog.com/entry/2024/03/16/224034
// O(Nlog^2N)
template <typename mint>
vc<mint> compositional_inverse(vc<mint> f) {
  /*
  仮定：[x^1]f = c は 0 ではない.
  f を改めて cf と書く. f の逆関数を g とすれば
  g(cf(x)/c)=x なので g(x/c) が求めるもの．よって [x^1]f=1 に帰着.

  f, g は n 次とする. Lagrange inversion formula
  n[x^n]f(x)^i = [x^{n-i}] i(g(x)/x)^{-n}
  左辺を i=1,...,n で求めると (g(x)/x)^{-n} が n-1 次まで求まる.
  [x^1]g=1 に帰着していたので -1/n 乗根がとれて, g(x)/x が n-1 次まで求まる.
  */
  const int n = len(f) - 1;
  if (n == -1) return {};
  assert(f[0] == mint(0));
  if (n == 0) return f;
  assert(f[1] != mint(0));
  mint c = f[1];
  for (auto& x: f) x /= c;

  vc<mint> A = coef_of_fps_pows<mint>(f, n, n);
  vc<mint> g(n);
  FOR(i, 1, n + 1) g[n - i] = mint(n) * A[i] * inv<mint>(i);
  g = fps_pow_1<mint>(g, -inv<mint>(n));
  g.insert(g.begin(), 0);

  mint pow = 1;
  FOR(i, len(g)) g[i] *= pow, pow /= c;
  return g;
}

using mint = modint998;

void solve() {
  int N;
  scanf("%d", &N);
  vc<mint> F(N);
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    F[i] = x;
  }
  F = compositional_inverse<mint>(F);
  FOR(i, N) {
    if (i) printf(" ");
    printf("%d", F[i].val);
  }
  printf("\n");
}

signed main() { solve(); }
