#include <assert.h>
#include <stdio.h>
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

template<int M>
vector<ModInt<M>> findLinearRecurrence(const vector<ModInt<M>> &as) {
  const int n = as.size();
  int d = 0, m = 0;
  vector<ModInt<M>> cs(n + 1, 0), bs(n + 1, 0);
  cs[0] = bs[0] = 1;
  ModInt<M> invBef = 1;
  for (int i = 0; i < n; ++i) {
    ++m;
    ModInt<M> dif = as[i];
    for (int j = 1; j <= d; ++j) dif += cs[j] * as[i - j];
    if (dif.x != 0) {
      auto csDup = cs;
      const ModInt<M> r = dif * invBef;
      for (int j = m; j < n; ++j) cs[j] -= r * bs[j - m];
      if (2 * d <= i) {
        d = i + 1 - d;
        m = 0;
        bs = csDup;
        invBef = dif.inv();
      }
    }
  }
  cs.resize(d + 1);
  return cs;
}

constexpr int MO = 998244353;
using Mint = ModInt<MO>;

int main() {
  int N;
  for (; ~scanf("%d", &N); ) {
    vector<Mint> as(N);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &as[i].x);
    }
    const auto cs = findLinearRecurrence(as);
    const int d = (int)cs.size() - 1;
    printf("%d\n", d);
    for (int j = 1; j <= d; ++j) {
      if (j > 1) printf(" ");
      printf("%d", (-cs[j]).x);
    }
    puts("");
  }
  return 0;
}
