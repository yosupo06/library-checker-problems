#include <cassert>
#include <cstdio>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;

template <u32 mod> struct Z {

  static_assert(mod > 1);
  static_assert(mod < (1U << 31));

  u32 v_;

  Z() = default;
  Z(u32 v) : v_(v % mod) {}
  Z(int v) : v_((v % int(mod) + int(mod)) % mod) {}
  Z(const Z &) = default;
  ~Z() = default;

  Z &operator=(const Z &rhs) {
    v_ = rhs.v_;
    return *this;
  }

  Z operator-() const { return Z(mod - v_); }
  Z &operator+=(const Z &rhs) {
    v_ += rhs.v_;
    if (v_ >= mod) v_ -= mod;
    return *this;
  }
  Z &operator-=(const Z &rhs) {
    v_ = v_ + mod - rhs.v_;
    if (v_ >= mod) v_ -= mod;
    return *this;
  }
  Z &operator*=(const Z &rhs) {
    v_ = u64(v_) * rhs.v_ % mod;
    return *this;
  }
  Z &operator/=(const Z &rhs) { return operator*=(rhs.inv()); }

  Z inv() const { // `mod` should be a prime number
    assert(v_ != 0);
    return pow(mod - 2);
  }
  Z pow(int e) const {
    if (e < 0) return inv().pow(-e);
    Z res(1), x(*this);
    for (; e; e >>= 1) {
      if (e & 1) res *= x;
      x *= x;
    }
    return res;
  }
  friend Z operator+(const Z &lhs, const Z &rhs) { return Z(lhs) += rhs; }
  friend Z operator-(const Z &lhs, const Z &rhs) { return Z(lhs) -= rhs; }
  friend Z operator*(const Z &lhs, const Z &rhs) { return Z(lhs) *= rhs; }
  friend Z operator/(const Z &lhs, const Z &rhs) { return Z(lhs) /= rhs; }
  friend bool operator==(const Z &lhs, const Z &rhs) { return lhs.v_ == rhs.v_; }
  friend bool operator!=(const Z &lhs, const Z &rhs) { return lhs.v_ != rhs.v_; }
};

template <typename T> T trace(const std::vector<std::vector<T>> &m) {
  int n = m.size();
  T s = 0;
  for (int i = 0; i < n; ++i) s += m[i][i];
  return s;
}

template <u32 mod>
std::vector<std::vector<Z<mod>>> matrix_mul(const std::vector<std::vector<Z<mod>>> &a,
                                            const std::vector<std::vector<Z<mod>>> &b) {
  int n = a.size(), m = b[0].size(), l = a[0].size();
  std::vector<std::vector<Z<mod>>> res(n, std::vector<Z<mod>>(m, Z<mod>(0)));
  for (int i = 0; i != n; ++i) {
    for (int k = 0; k != l; ++k) {
      for (int j = 0; j != m; ++j) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return res;
}

int main() {
  const u32 MOD = 998244353;
  int n;
  std::scanf("%d", &n);

  if (n > 50) return 1; // TLE

  std::vector<std::vector<Z<MOD>>> m(n, std::vector<Z<MOD>>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int v;
      std::scanf("%d", &v);
      m[i][j] = Z<MOD>(v);
    }
  }

  // reference: https://en.wikipedia.org/wiki/Faddeev%E2%80%93LeVerrier_algorithm

  std::vector<std::vector<Z<MOD>>> b(n, std::vector<Z<MOD>>(n, Z<MOD>(0)));
  for (int i = 0; i != n; ++i) b[i][i] = 1; // identity matrix
  std::vector<Z<MOD>> p(n + 1);
  p.back() = Z<MOD>(1);

  for (int i = n - 1, k = 1; i >= 0; --i, ++k) {
    b = matrix_mul(m, b);
    p[i] = -Z<MOD>(k).inv() * trace(b);
    for (int j = 0; j != n; ++j) b[j][j] += p[i];
  }
  for (int i = 0; i <= n; ++i) {
    std::printf("%d", int(p[i].v_));
    if (i != n) std::printf(" ");
  }
  std::printf("\n");
  return 0;
}