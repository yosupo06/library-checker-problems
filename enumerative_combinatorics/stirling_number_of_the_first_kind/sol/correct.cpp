// O(N log N)

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
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
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

// M: prime, G: primitive root
template <int M, int G, int K> struct Fft {
  using Mint = ModInt<M>;
  // 1, 1/4, 1/8, 3/8, 1/16, 5/16, 3/16, 7/16, ...
  Mint g[1 << (K - 1)];
  constexpr Fft() : g() {
    static_assert(K >= 2, "Fft: K >= 2 must hold");
    static_assert(!((M - 1) & ((1 << K) - 1)), "Fft: 2^K | M - 1 must hold");
    g[0] = 1;
    g[1 << (K - 2)] = Mint(G).pow((M - 1) >> K);
    for (int l = 1 << (K - 2); l >= 2; l >>= 1) {
      g[l >> 1] = g[l] * g[l];
    }
    assert((g[1] * g[1]).x == M - 1);
    for (int l = 2; l <= 1 << (K - 2); l <<= 1) {
      for (int i = 1; i < l; ++i) {
        g[l + i] = g[l] * g[i];
      }
    }
  }
  void fft(vector<Mint> &x) const {
    const int n = x.size();
    assert(!(n & (n - 1)) && n <= 1 << K);
    for (int l = n; l >>= 1; ) {
      for (int i = 0; i < (n >> 1) / l; ++i) {
        for (int j = (i << 1) * l; j < (i << 1 | 1) * l; ++j) {
          const Mint t = g[i] * x[j + l];
          x[j + l] = x[j] - t;
          x[j] += t;
        }
      }
    }
    for (int i = 0, j = 0; i < n; ++i) {
      if (i < j) std::swap(x[i], x[j]);
      for (int l = n; (l >>= 1) && !((j ^= l) & l); ) {}
    }
  }
  vector<Mint> convolution(const vector<Mint> &a, const vector<Mint> &b) const {
    const int na = a.size(), nb = b.size();
    int n, invN = 1;
    for (n = 1; n < na + nb - 1; n <<= 1) invN = ((invN & 1) ? (invN + M) : invN) >> 1;
    vector<Mint> x(n, 0), y(n, 0);
    std::copy(a.begin(), a.end(), x.begin());
    std::copy(b.begin(), b.end(), y.begin());
    fft(x);
    fft(y);
    for (int i = 0; i < n; ++i) x[i] = x[i] * y[i] * invN;
    std::reverse(x.begin() + 1, x.end());
    fft(x);
    x.resize(na + nb - 1);
    return x;
  }
};

constexpr int MO = 998244353;
const Fft<MO, 3, 20> FFT;
using Mint = ModInt<MO>;

constexpr int LIM = 500010;
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

vector<Mint> stirling1(int n) {
  if (n == 0) return {1};
  int m = 1;
  vector<Mint> s{0, 1};
  for (int e = 31 - __builtin_clz(n) - 1; e >= 0; --e) {
    // X -> X - m
    vector<Mint> as(m + 1), bs(m + 1);
    for (int i = 0; i <= m; ++i) as[i] = fac[i] * s[i];
    bs[m - 0] = 1;
    for (int i = 1; i <= m; ++i) bs[m - i] = bs[m - (i - 1)] * -m;
    for (int i = 0; i <= m; ++i) bs[m - i] *= invFac[i];
    const vector<Mint> cs = FFT.convolution(as, bs);
    vector<Mint> ds(m + 1);
    for (int i = 0; i <= m; ++i) ds[i] = invFac[i] * cs[m + i];
    s = FFT.convolution(s, ds);
    m <<= 1;
    if (n & 1 << e) {
      // multiply by (X - m)
      vector<Mint> ss(m + 1 + 1, 0);
      for (int i = 0; i <= m; ++i) {
        ss[i] += s[i] * -m;
        ss[i + 1] += s[i];
      }
      s = ss;
      m |= 1;
    }
  }
  assert(m == n);
  return s;
}

int main() {
  prepareFac();
  int N;
  for (; ~scanf("%d", &N); ) {
    const auto ans = stirling1(N);
    for (int k = 0; k <= N; ++k) {
      if (k > 0) printf(" ");
      printf("%d", ans[k].x);
    }
    puts("");
  }
  return 0;
}
