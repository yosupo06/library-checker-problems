#include <cstdio>
#include <array>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;

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

#define FOR_subset(t, s) \
  for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

int popcnt(int x) { return __builtin_popcount(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }

template <typename T, int LIM>
vc<array<T, LIM + 1>> ranked_zeta(const vc<T> &f) {
  int n = topbit(len(f));
  assert(n <= LIM);
  assert(len(f) == 1 << n);
  vc<array<T, LIM + 1>> Rf(1 << n);
  for (int s = 0; s < (1 << n); ++s) Rf[s][popcnt(s)] = f[s];
  for (int i = 0; i < n; ++i) {
    int w = 1 << i;
    for (int p = 0; p < (1 << n); p += 2 * w) {
      for (int s = p; s < p + w; ++s) {
        int t = s | 1 << i;
        for (int d = 0; d <= n; ++d) Rf[t][d] += Rf[s][d];
      }
    }
  }
  return Rf;
}

template <typename T, int LIM>
vc<T> ranked_mobius(vc<array<T, LIM + 1>> &Rf) {
  int n = topbit(len(Rf));
  assert(len(Rf) == 1 << n);
  for (int i = 0; i < n; ++i) {
    int w = 1 << i;
    for (int p = 0; p < (1 << n); p += 2 * w) {
      for (int s = p; s < p + w; ++s) {
        int t = s | 1 << i;
        for (int d = 0; d <= n; ++d) Rf[t][d] -= Rf[s][d];
      }
    }
  }
  vc<T> f(1 << n);
  for (int s = 0; s < (1 << n); ++s) f[s] = Rf[s][popcnt(s)];
  return f;
}

template <typename T, int LIM = 20>
vc<T> subset_convolution(const vc<T> &A, const vc<T> &B) {
  auto RA = ranked_zeta<T, LIM>(A);
  auto RB = ranked_zeta<T, LIM>(B);
  int n = topbit(len(RA));
  FOR(s, len(RA)) {
    auto &f = RA[s], &g = RB[s];
    FOR_R(d, n + 1) {
      T x = 0;
      FOR(i, d + 1) x += f[i] * g[d - i];
      f[d] = x;
    }
  }
  return ranked_mobius<T, LIM>(RA);
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
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
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
};

template <class T>
vc<T> convolution_naive(const vc<T> &a, const vc<T> &b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vector<T> ans(n + m - 1);
  FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  return ans;
}

// for fixed sps s, consider linear map F:a->b = subset-conv(a,s)
// given x, calculate transpose(F)(x)
template <typename mint, int LIM>
vc<mint> transposed_subset_convolution(vc<mint> s, vc<mint> x) {
  /*
  sum_{j}x_jb_j = sum_{i subset j}x_ja_is_{j-i} = sum_{i}y_ia_i.
  y_i = sum_{j supset i}x_js_{j-i}
  (rev y)_i = sum_{j subset i}(rev x)_js_{i-j}
  y = rev(conv(rev x), s)
  */
  reverse(all(x));
  x = subset_convolution<mint, LIM>(x, s);
  reverse(all(x));
  return x;
}

// for fixed sps s s.t. s[0] == 0.
// consider linear map F:f->t=f(s) for egf f.
// given x, calcuate transpose(F)(x)
// equivalent: calculate sum_i x_i(s^k/k!)_i for k=0,1,...,N
template <typename mint, int LIM>
vc<mint> transposed_sps_composition_egf(vc<mint> &s, vc<mint> x) {
  const int N = topbit(len(s));
  assert(len(s) == (1 << N) && len(x) == (1 << N) && s[0] == mint(0));
  vc<mint> y(N + 1);
  y[0] = x[0];
  auto &dp = x;
  FOR(i, N) {
    vc<mint> newdp(1 << (N - 1 - i));
    FOR(j, N - i) {
      vc<mint> a = {s.begin() + (1 << j), s.begin() + (2 << j)};
      vc<mint> b = {dp.begin() + (1 << j), dp.begin() + (2 << j)};
      b = transposed_subset_convolution<mint, LIM>(a, b);
      FOR(k, len(b)) newdp[k] += b[k];
    }
    swap(dp, newdp);
    y[1 + i] = dp[0];
  }
  return y;
}

// for fixed sps s s.t. s[0] == 0.
// consider linear map F:f->t=f(s) for polynomial f.
// given x, calcuate transpose(F)(x)
// equivalent: calculate sum_i x_i(s^k/k!)_i for k=0,1,...,M-1
template <typename mint, int LIM>
vc<mint> transposed_sps_composition_poly(vc<mint> s, vc<mint> x, int M) {
  const int N = topbit(len(s));
  assert(len(s) == (1 << N) && len(x) == (1 << N));
  mint c = s[0];
  s[0] -= c;
  x = transposed_sps_composition_egf<mint, LIM>(s, x);
  vc<mint> g(M);
  mint pow = 1;
  FOR(i, M) { g[i] = pow * fact_inv<mint>(i), pow *= c; }
  x = convolution_naive<mint>(x, g);
  x.resize(M);
  FOR(i, M) x[i] *= fact<mint>(i);
  return x;
}

using mint = modint<998244353>;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);
  vc<mint> s(1 << N), w(1 << N);
  FOR(i, 1 << N) {
    int x;
    scanf("%d", &x);
    s[i] = x;
  }
  FOR(i, 1 << N) {
    int x;
    scanf("%d", &x);
    w[i] = x;
  }
  vc<mint> ANS = transposed_sps_composition_poly<mint, 20>(s, w, M);
  FOR(i, M) {
    if (i) printf(" ");
    printf("%d", ANS[i].val);
  }
  printf("\n");
}

signed main() {
  solve();
  return 0;
}
