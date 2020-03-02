#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

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

using Mint = ModInt<MOD>;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  int N, d;
  switch (seed % 3) {
    case 0: {
      N = N_MAX;
      d = N - 1;
    } break;
    case 1: {
      N = N_MAX;
      d = rng.uniform(N / 8 * 5, N / 8 * 7);
    } break;
    case 2: {
      N = N_MAX - 1;
      d = rng.uniform(N / 8 * 5, N / 8 * 7);
    } break;
    default: assert(false);
  }
  vector<Mint> cs(d + 1);
  for (int j = 1; j < d; ++j) {
    cs[j] = rng.uniform(0LL, MOD - 1);
  }
  cs[d] = rng.uniform(1LL, MOD - 1);
  vector<Mint> as(N);
  as[0] = 1;
  as[1] = rng.uniform(2LL, MOD - 2);
  for (int i = 1; i < d; ++i) {
    as[i] = as[i - 1] * as[1];
  }
  for (int i = d; i < N; ++i) {
    Mint sum = 0;
    for (int j = 1; j <= d; ++j) {
      sum += cs[j] * as[i - j];
    }
    as[i] = sum;
  }

  printf("%d\n", N);
  for (int i = 0; i < N; ++i) {
    if (i > 0) printf(" ");
    printf("%d", as[i].x);
  }
  puts("");
  return 0;
}
