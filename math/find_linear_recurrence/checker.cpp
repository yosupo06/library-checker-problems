#include "testlib.h"
#include <assert.h>
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
    ModInt x2 = x, xe = 1;
    for (; e; e >>= 1) {
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

constexpr int MO = 998244353;
using Mint = ModInt<MO>;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  const int N = inf.readInt();
  vector<Mint> as(N);
  for (int i = 0; i < N; ++i) {
    as[i] = inf.readInt();
  }

  const int d = ouf.readInt(0, N);
  vector<Mint> cs(d + 1);
  for (int j = 1; j <= d; ++j) {
    cs[j] = ouf.readInt(0, MO - 1);
  }
  for (int i = d; i < N; ++i) {
    Mint sum = 0;
    for (int j = 1; j <= d; ++j) {
      sum += cs[j] * as[i - j];
    }
    if (as[i].x != sum.x) {
      quitf(_wa, "a_i = \\sum_{j=1}^d c_j a_{i-j} must hold");
    }
  }

  const int dAns = ans.readInt();
  if (dAns < d) {
    quitf(_wa, "d is not minimized");
  } else if (dAns > d) {
    quitf(_fail, "better than judge!");
  } else {
    quitf(_ok, "OK");
  }

  return 0;
}
