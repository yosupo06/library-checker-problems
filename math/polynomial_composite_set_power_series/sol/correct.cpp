// Reference : https://codeforces.com/blog/entry/92183

#pragma GCC target("bmi,popcnt")

#include <algorithm>
#include <cassert>
#include <vector>

namespace noshi91 {

namespace composition_egf_sps_internal {

template <class T, class F> void bitwise_transform(std::vector<T> &a, F f) {
  const int n = a.size();
  for (int w = 1; w < n; w *= 2) {
    for (int i = 0; i < n; i += w * 2) {
      for (int j = 0; j < w; j++) {
        f(a[i + j], a[i + w + j]);
      }
    }
  }
}

// f: sequence of length n + 1
// s: n variable set power series, constant term is 0
// output: \sum_{k=0}^{n} f_k s^k / k!
template <class T>
std::vector<T> composition_egf_sps(const std::vector<T> &f,
                                   const std::vector<T> &s) {
  const int n = int(f.size()) - 1;
  assert(0 <= n && n <= 30);
  assert(int(s.size()) == 1 << n);

  std::vector<std::vector<std::vector<T>>> a(n + 1);
  for (int i = 0; i <= n; i++) {
    a[i].assign(i + 1, std::vector<T>(1 << i));
    a[i][0][0] = f[n - i];
  }

  for (int v = 0; v < n; v++) {
    std::vector h(v + 1, std::vector<T>(1 << v));
    for (int i = 0; i < 1 << v; i++)
      h[__builtin_popcount(i)][i] = s[(1 << v) + i];
    for (int i = 0; i <= v; i++)
      bitwise_transform(h[i], [](T &l, T &r) { r += l; });
    for (int i = v + 1; i <= n; i++) {
      for (int j = 0; j <= i; j++) {
        std::copy_n(a[i][j].begin(), 1 << v, a[i][j].begin() + (1 << v));
      }
    }
    for (int i = v; i < n; i++) {
      for (int j = 0; j <= v; j++) {
        for (int k = 0; j + k <= i; k++) {
          for (int p = 0; p < 1 << v; p++) {
            a[i + 1][j + k + 1][(1 << v) + p] += h[j][p] * a[i][k][p];
          }
        }
      }
    }
  }

  for (int i = 0; i <= n; i++)
    bitwise_transform(a[n][i], [](T &l, T &r) { r -= l; });
  std::vector<T> t(1 << n);
  for (int i = 0; i < 1 << n; i++)
    t[i] = a[n][__builtin_popcount(i)][i];
  return t;
}

// f: polynomial
// s: set power series
// output: f(s)
template <class T>
std::vector<T> composition_poly_sps(std::vector<T> f, const std::vector<T> &s) {
  assert(!s.empty());
  const int n = __builtin_ctz(s.size());
  assert(int(s.size()) == 1 << n);
  std::vector<T> eval(n + 1, T(0));
  const T c = s[0];
  for (int i = 0; i <= n && !f.empty(); i++) {
    T t = 0;
    for (int j = f.size(); j-- > 0;)
      t = t * c + f[j];
    eval[i] = t;
    for (int j = 1; j < int(f.size()); j++)
      f[j - 1] = f[j] * j;
    f.pop_back();
  }
  return composition_egf_sps(eval, s);
}

} // namespace composition_egf_sps_internal

using composition_egf_sps_internal::composition_egf_sps;
using composition_egf_sps_internal::composition_poly_sps;

} // namespace noshi91

#include <cstdio>

constexpr int mod = 998244353;
using ll = long long;
struct mm {
  int x;
  mm() : x(0) {}
  mm(ll x_) : x(x_ % mod) {
    if (x < 0)
      x += mod;
  }
  mm &operator+=(mm b) {
    if ((x += b.x) >= mod)
      x -= mod;
    return *this;
  }
  mm &operator-=(mm b) {
    if ((x -= b.x) < 0)
      x += mod;
    return *this;
  }
  mm &operator*=(mm b) {
    x = ll(x) * b.x % mod;
    return *this;
  }
  mm &operator/=(mm b) { return *this *= b.pow(mod - 2); }
  friend mm operator+(mm a, mm b) { return a += b; }
  friend mm operator-(mm a, mm b) { return a -= b; }
  friend mm operator*(mm a, mm b) { return a *= b; }
  friend mm operator/(mm a, mm b) { return a /= b; }
  mm pow(ll e) const {
    mm r = 1, b = *this;
    while (e) {
      if (e & 1)
        r *= b;
      b *= b;
      e >>= 1;
    }
    return r;
  }
};

using mint = mm;

int main() {
  int M, N;
  scanf("%d%d", &M, &N);
  std::vector<mint> f(M), s(1 << N);
  for (auto &e : f) {
    int t;
    scanf("%d", &t);
    e = t;
  }
  for (auto &e : s) {
    int t;
    scanf("%d", &t);
    e = t;
  }

  auto ans = noshi91::composition_poly_sps(f, s);
  for (int i = 0; i < 1 << N; i++) {
    printf("%d%c", ans[i].x, " \n"[i + 1 == 1 << N]);
  }

  return 0;
}
