// O(d log log d)

#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

template<int M_> struct ModInt {
  static constexpr int M = M_;
  int x;
  constexpr ModInt() : x(0) {}
  constexpr ModInt(long long x_) : x(x_ % M) { if (x < 0) x += M; }
  ModInt &operator+=(const ModInt &a) { x += a.x; if (x >= M) x -= M; return *this; }
  ModInt &operator-=(const ModInt &a) { x -= a.x; if (x < 0) x += M; return *this; }
  ModInt &operator*=(const ModInt &a) { x = static_cast<int>((static_cast<long long>(x) * a.x) % M); return *this; }
  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
  ModInt operator-() const { return ModInt(-x); }
  ModInt pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModInt x2 = x, xe = 1;
    for (; e > 0; e >>= 1) {
      if (e & 1) xe *= x2;
      x2 *= x2;
    }
    return xe;
  }
  ModInt inv() const {
    int a = x, b = M, y = 1, z = 0, t;
    for (; ; ) {
      t = a / b; a -= t * b;
      if (a == 0) {
        assert(b == 1 || b == -1);
        return ModInt(b * z);
      }
      y -= t * z;
      t = b / a; b -= t * a;
      if (b == 0) {
        assert(a == 1 || a == -1);
        return ModInt(a * y);
      }
      z -= t * y;
    }
  }
  friend ModInt operator+(long long a, const ModInt &b) { return (ModInt(a) += b); }
  friend ModInt operator-(long long a, const ModInt &b) { return (ModInt(a) -= b); }
  friend ModInt operator*(long long a, const ModInt &b) { return (ModInt(a) *= b); }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};

constexpr int MO = 998'244'353;
using Mint = ModInt<MO>;

constexpr int LIM = 10'000'010;
Mint inv[LIM], fac[LIM], invFac[LIM];

void prepareFac() {
  inv[1] = 1;
  for (int i = 2; i < LIM; ++i) {
    inv[i] = -(Mint::M / i) * inv[Mint::M % i];
  }
  fac[0] = invFac[0] = 1;
  for (int i = 1; i < LIM; ++i) {
    fac[i] = fac[i - 1] * i;
    invFac[i] = invFac[i - 1] * inv[i];
  }
}

// pws[i] = i^d
vector<Mint> getMonomials(long long d, int n) {
  vector<int> lpf(n);
  for (int i = 2; i < n; ++i) lpf[i] = i;
  for (int p = 2; p < n; ++p) if (lpf[p] == p) {
    for (int i = 2 * p; i < n; i += p) if (lpf[i] > p) lpf[i] = p;
  }
  vector<Mint> pws(n);
  for (int i = 0; i < n; ++i) {
    pws[i] = (i <= 1 || lpf[i] == i) ? Mint(i).pow(d) : (pws[lpf[i]] * pws[i / lpf[i]]);
  }
  return pws;
}

// \sum_{i=0}^{\infty} r^i f(i) (deg f <= d)
Mint sumPowerPolyLimit(Mint r, int d, const vector<Mint> &fs) {
  assert(r.x != 1);
  assert(d + 1 < LIM);
  assert(fs.size() >= static_cast<size_t>(d + 1));
  vector<Mint> rr(d + 1);
  rr[0] = 1;
  for (int i = 1; i <= d; ++i) rr[i] = rr[i - 1] * r;
  Mint ans = 0, sumRF = 0;
  for (int i = 0; i <= d; ++i) {
    sumRF += rr[i] * fs[i];
    ans += invFac[d - i] * invFac[i + 1] * (((d - i) & 1) ? -1 : +1) *
           rr[d - i] * sumRF;
  }
  ans *= (1 - r).pow(-(d + 1)) * fac[d + 1];
  return ans;
}

// \sum_{i=0}^{\infty} r^i i^d
Mint sumPowerPolyLimit(Mint r, int d) {
  return sumPowerPolyLimit(r, d, getMonomials(d, d + 1));
}

int main() {
  prepareFac();
  Mint r;
  int d;
  for (; ~scanf("%d%d", &r.x, &d); ) {
    const Mint ans = sumPowerPolyLimit(r, d);
    printf("%d\n", ans.x);
  }
  return 0;
}
