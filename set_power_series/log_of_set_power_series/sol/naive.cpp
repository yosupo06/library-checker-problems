#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using std::vector;

////////////////////////////////////////////////////////////////////////////////
template <unsigned M_> struct ModInt {
  static constexpr unsigned M = M_;
  unsigned x;
  constexpr ModInt() : x(0U) {}
  constexpr ModInt(unsigned x_) : x(x_ % M) {}
  constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
  constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
  constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
  ModInt pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  ModInt inv() const {
    unsigned a = M, b = x; int y = 0, z = 1;
    for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
    assert(a == 1U); return ModInt(y);
  }
  ModInt operator+() const { return *this; }
  ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
  template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
  template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
  template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
  template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const ModInt &a) const { return (x == a.x); }
  bool operator!=(const ModInt &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};
////////////////////////////////////////////////////////////////////////////////

constexpr unsigned MO = 998244353;
using Mint = ModInt<MO>;


int main() {
  int N;
  scanf("%d", &N);
  vector<Mint> B(1 << N);
  for (int i = 0; i < 1 << N; ++i) {
    scanf("%u", &B[i].x);
  }

  vector<Mint> G = B; // G = B - 1
  G[0] -= 1;

  vector<Mint> ans(1 << N, 0);

  // log(1 + G) = sum_{k >= 1} (-1)^{k - 1} G^k / k
  vector<Mint> ps = G; // ps = G^k
  for (int k = 1; k <= N; ++k) {
    const Mint k_inv = Mint(k).inv();
    if (k & 1) {
      for (int i = 0; i < 1 << N; ++i) ans[i] += ps[i] * k_inv;
    } else {
      for (int i = 0; i < 1 << N; ++i) ans[i] -= ps[i] * k_inv;
    }

    vector<Mint> qs(1 << N, 0);
    for (int i = 0; i < 1 << N; ++i) {
      for (int j = i; ; --j &= i) {
        qs[i] += ps[j] * G[i - j];
        if (!j) break;
      }
    }
    ps = qs;
  }

  for (int i = 0; i < 1 << N; ++i) {
    if (i) printf(" ");
    printf("%u", ans[i].x);
  }
  puts("");
  return 0;
}
