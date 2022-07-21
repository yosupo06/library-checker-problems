#include <iostream>
#include <vector>

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

  mint f0 = f[0].second;
  mint g0 = mint(1) / f0;

  f.erase(f.begin());

  vector<mint> g(N);
  g[0] = g0;

  for (int n = 1; n < N; ++n) {
    // sum f[i]g[n-i] = 0
    // f0g[n] = -sum f[i]g[n-i]
    mint rhs = 0;
    for (auto &&[i, fi]: f) {
      if (i <= n) rhs -= fi * g[n - i];
    }
    g[n] = rhs * g0;
  }

  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", g[i].val);
  }
  printf("\n");
  return 0;
}
