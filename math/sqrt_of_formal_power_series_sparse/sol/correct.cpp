#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

using namespace std;

using u32 = unsigned int;
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

template <typename mint>
mint mod_sqrt(mint a) {
  int p = mint::get_mod();
  if (p == 2) return a;
  if (a == 0) return 0;
  int k = (p - 1) / 2;
  if (a.pow(k) != 1) return 0;
  auto find = [&]() -> pair<mint, mint> {
    mint b = mint(1);
    while (1) {
      b += mint(1);
      mint D = b * b - a;
      if (D == 0) return {b, D};
      if (D.pow(k) != mint(1)) return {b, D};
    }
    return {mint(0), mint(0)};
  };
  auto [b, D] = find();
  if (D == 0) return b;
  ++k;
  // (b + sqrt(D))^k
  mint f0 = b, f1 = 1;
  mint g0 = 1, g1 = 0;
  while (k) {
    if (k & 1) {
      std::tie(g0, g1) = make_pair(f0 * g0 + D * f1 * g1, f1 * g0 + f0 * g1);
    }
    std::tie(f0, f1) = make_pair(f0 * f0 + D * f1 * f1, mint(2) * f0 * f1);
    k >>= 1;
  }
  return g0;
}

template <typename mint>
vc<mint> fps_sqrt(vc<mint> &f) {
  assert(f[0] == mint(1));
  return fps_pow_1_sparse(f, inv<mint>(2));
}

template <typename mint>
vc<mint> fps_sqrt_any(vc<mint> &f) {
  int n = f.size();
  int d = n;
  for (int i = n - 1; i >= 0; --i)
    if (f[i] != 0) d = i;
  if (d == n) return f;
  if (d & 1) return {};
  mint y = f[d];
  mint x = mod_sqrt(y);
  if (x * x != y) return {};
  mint c = mint(1) / y;
  vc<mint> g(n - d);
  for (int i = 0; i < n - d; ++i) g[i] = f[d + i] * c;
  g = fps_sqrt(g);
  for (int i = 0; i < int(g.size()); ++i) g[i] *= x;
  g.resize(n);
  for (int i = n - 1; i >= 0; --i) {
    if (i >= d / 2)
      g[i] = g[i - d / 2];
    else
      g[i] = 0;
  }
  return g;
}

using mint = modint<998244353>;

int main() {
  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);

  vc<mint> f(N);
  for (int k = 0; k < K; ++k) {
    int i, a;
    scanf("%d", &i);
    scanf("%d", &a);
    f[i] = mint(a);
  }

  f = fps_sqrt_any(f);
  if (f.empty()) {
    printf("%d", -1);
    printf("\n");
    return 0;
  }

  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", f[i].val);
  }
  printf("\n");

  return 0;
}
