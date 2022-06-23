#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

using u32 = uint;
using ll = long long;

template <class T>
using vc = vector<T>;

template <u32 mod>
struct modint {
  static constexpr bool is_modint = true;
  u32 val;
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
    val = (u32)(1LL * val * p.val % mod);
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
  static constexpr u32 get_mod() { return mod; }
};

template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (int(dat.size()) <= n) {
    int k = dat.size();
    auto q = (mod + k - 1) / k;
    int r = k * q - mod;
    dat.emplace_back(dat[r] * mint(q));
  }
  return dat[n];
}

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {1, 1};
  assert(0 <= n);
  if (n >= mod) return 0;
  while (int(dat.size()) <= n) {
    int k = dat.size();
    dat.emplace_back(dat[k - 1] * mint(k));
  }
  return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {1, 1};
  assert(0 <= n && n < mod);
  while (int(dat.size()) <= n) {
    int k = dat.size();
    dat.emplace_back(dat[k - 1] * inv<mint>(k));
  }
  return dat[n];
}

template <typename mint>
vc<mint> fps_pow(const vc<mint> &f, ll k) {
  int n = f.size();
  int d = n;
  for (int i = n - 1; i >= 0; --i)
    if (f[i] != mint(0)) d = i;
  ll off = d * k;
  if (off >= n) return vc<mint>(n, mint(0));
  mint c = f[d];
  mint c_inv = mint(1) / mint(c);
  vc<mint> g(n - off);
  for (int i = 0; i < n - off; ++i) g[i] = f[d + i] * c_inv;
  g = fps_pow_1_sparse(g, mint(k));
  vc<mint> h(n);
  c = c.pow(k);
  for (int i = 0; i < int(g.size()); ++i) h[off + i] = g[i] * c;
  return h;
}

template <typename mint>
vc<mint> fps_pow_1_sparse(const vc<mint> &f, mint K) {
  int N = f.size();
  vc<pair<int, mint>> dat;
  for (int i = 1; i < N; ++i)
    if (f[i] != mint(0)) dat.emplace_back(i, f[i]);
  vc<mint> g(N);
  g[0] = 1;
  for (int n = 0; n < N - 1; ++n) {
    mint &x = g[n + 1];
    for (auto &&[d, cf]: dat) {
      if (d > n + 1) break;
      mint t = cf * g[n - d + 1];
      x += t * (K * mint(d) - mint(n - d + 1));
    }
    x *= inv<mint>(n + 1);
  }
  return g;
}

using mint = modint<998244353>;

int main() {
  int N, K, M;
  scanf("%d", &N);
  scanf("%d", &K);
  scanf("%d", &M);

  vc<mint> f(N);
  for (int k = 0; k < K; ++k) {
    int i, a;
    scanf("%d", &i);
    scanf("%d", &a);
    f[i] = mint(a);
  }

  f = fps_pow(f, M);

  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", f[i].val);
  }
  printf("\n");

  return 0;
}
