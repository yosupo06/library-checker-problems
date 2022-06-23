#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

using u32 = unsigned int;
using ll = long long;

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

using mint = modint<998244353>;

int main() {
  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);

  vector<pair<int, mint>> f;
  for (int k = 0; k < K; ++k) {
    int i, a;
    scanf("%d", &i);
    scanf("%d", &a);
    f.emplace_back(i, mint(a));
  }

  // df
  vector<pair<int, mint>> df;
  for(auto&& [i, fi] : f) df.emplace_back(i - 1, mint(i) * fi);

  // F = exp f
  vector<mint> F(N);
  F[0] = 1;
  for(int n = 1; n < N; ++n){
    mint rhs = 0;
    for (auto&& [k, fk]: df) {
      if (k > n - 1) break;
      rhs += fk * F[n - 1 - k];
    }
    F[n] = rhs * inv<mint>(n);
  }

  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", F[i].val);
  }
  printf("\n");
  return 0;
}

