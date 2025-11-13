#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>
#include <cstdint>

using namespace std;
using ll = long long;

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

  using T = tuple<ll, ll, ll, ll, mint>;
  vector<T> dat;
  for (int n = 0; n < N; ++n) {
    ll l, d, r, u, w;
    scanf("%lld %lld %lld %lld %lld", &l, &d, &r, &u, &w);
    dat.emplace_back(l, d, r, u, w);
  }

  for (int q = 0; q < Q; ++q) {
    ll l1, d1, r1, u1;
    scanf("%lld %lld %lld %lld", &l1, &d1, &r1, &u1);

    mint sm = 0;
    for (auto &&[l2, d2, r2, u2, w]: dat) {
      ll l = max(l1, l2);
      ll r = min(r1, r2);
      ll d = max(d1, d2);
      ll u = min(u1, u2);
      ll dx = max(0LL, r - l);
      ll dy = max(0LL, u - d);
      ll area = dx * dy;
      sm += mint(area) * w;
    }
    printf("%d\n", sm.val);
  }

  return 0;
}
