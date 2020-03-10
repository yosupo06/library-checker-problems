// O(d log log d + log n)

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

Mint binom(long long n, long long k) {
  if (0 <= k && k <= n) {
    assert(n < LIM);
    return fac[n] * invFac[k] * invFac[n - k];
  } else {
    return 0;
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

// mukashi kaita
Mint sumPowerPoly(int d, const vector<Mint> &y, Mint a, long long n) {
  assert(d + 1 < LIM);
  assert((int)y.size() >= d + 1);
  if (n <= d + 1) {
    Mint sum = 0, aa = 1;
    for (int i = 0; i < n; ++i) {
      sum += aa * y[i];
      aa *= a;
    }
    return sum;
  } else {
    // a^i, a^(n-i), binom(n, i), binom(n - 1 - i, d - i)
    vector<Mint> a0(d + 1), a1(d + 1), c0(d + 2), c1(d + 2);
    a0[0] = 1;
    for (int i = 1; i <= d; ++i) a0[i] = a0[i - 1] * a;
    a1[d] = a.pow(n - d);
    for (int i = d - 1; i >= 0; --i) a1[i] = a1[i + 1] * a;
    c0[0] = 1;
    for (int i = 1; i <= d + 1; ++i) c0[i] = c0[i - 1] * (n + 1 - i) * inv[i];
    c1[d + 1] = 0; c1[d] = 1;
    for (int i = d - 1; i >= 0; --i) c1[i] = c1[i + 1] * (n - 1 - i) * inv[d - i];
    Mint b = 0;
    if (a.x == 1) {
      b = c0[d] * (n - d) * inv[d + 1];
    } else {
      b = 1;
      for (int i = 0; i <= d; ++i) {
        b -= c0[i] * c1[i] * (((d - i) % 2 != 0) ? -1 : +1) * a1[i];
      }
      b *= (1 - a).inv().pow(d + 1);
    }
    Mint ret = 0, sum = 0;
    for (int i = 1; i <= d + 1; ++i) {
      sum += a0[i - 1] * y[i - 1];
      ret += (b * binom(d + 1, i) * (((d + 1 - i) % 2 != 0) ? -1 : +1) * a0[d + 1 - i] +
          c0[i] * c1[i] * (((d - i) % 2 != 0) ? -1 : +1) * a1[i]) * sum;
    }
    return ret;
  }
}

int main() {
  prepareFac();
  Mint r;
  int d;
  long long n;
  for (; ~scanf("%d%d%lld", &r.x, &d, &n); ) {
    const vector<Mint> pws = getMonomials(d, d + 1);
    const Mint ans = sumPowerPoly(d, pws, r, n);
    printf("%d\n", ans.x);
  }
  return 0;
}
