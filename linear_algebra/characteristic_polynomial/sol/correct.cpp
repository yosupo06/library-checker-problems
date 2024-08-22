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

template <u32 mod> void reduce(std::vector<std::vector<Z<mod>>> &m) {
  // Gaussian elimination as similarity transformation
  // reduce the matrix to an upper Hessenberg matrix
  int n = m.size();
  if (n <= 2) return;
  for (int i = 0; i != n - 2; ++i) {
    int p = i + 1;
    for (; p != n; ++p) { // choose a pivot under the diagonal
      if (m[p][i] != 0) break;
    }
    if (p == n) continue;
    if (p != i + 1) {
      std::swap(m[p], m[i + 1]);                                    // swap rows
      for (int j = 0; j != n; ++j) std::swap(m[j][p], m[j][i + 1]); // swap cols
    }
    Z<mod> iv = m[i + 1][i].inv();
    for (int j = i + 2; j != n; ++j) {
      if (m[j][i] == 0) continue;
      Z<mod> v = m[j][i] * iv;
      for (int k = i; k != n; ++k)
        m[j][k] -= v * m[i + 1][k]; // subtract `v` * row(`i + 1`) from row(`j`)
      for (int k = 0; k != n; ++k) m[k][i + 1] += v * m[k][j]; // add `v` * col(`j`) to col(`i + 1`)
    }
  }
}

template <u32 mod> std::vector<Z<mod>> get_charpoly(const std::vector<std::vector<Z<mod>>> &m) {
  std::vector<std::vector<Z<mod>>> h = m;
  reduce(h);
  int n = h.size();
  std::vector<std::vector<Z<mod>>> p(n + 1); // `p[i]` is the charpoly of leading principal submatrix h_i
  p[0].resize(1);
  p[0][0] = Z<mod>(1); // let `p[0]` = 1
  if (n == 0) return p[0];
  p[1].resize(2);
  p[1][0] = -h[0][0];
  p[1][1] = Z<mod>(1); // let `p[1]` = x - `h[0][0]`
  for (int i = 2; i <= n; ++i) {
    const std::vector<Z<mod>> &pi_1 = p[i - 1];
    std::vector<Z<mod>> &pi = p[i];
    pi.resize(p[i - 1].size() + 1, Z<mod>(0)); // let `pi` = `pi_1` * (x - `h[i - 1][i - 1]`)
    for (int j = 0, je = pi_1.size(); j < je; ++j) pi[j] += pi_1[j] * -h[i - 1][i - 1];
    for (int j = 0, je = pi_1.size(); j < je; ++j) pi[j + 1] += pi_1[j];
    Z<mod> t(1); // `t` is the product of the subdiagonal
    for (int j = 1; j < i; ++j) {
      t *= h[i - j][i - j - 1];
      Z<mod> prod = t * h[i - j - 1][i - 1];
      if (prod == 0) continue;
      for (int k = 0; k <= i - j - 1; ++k) pi[k] -= prod * p[i - j - 1][k];
    }
  }
  return p[n];
}

int main() {
  const u32 MOD = 998244353;
  int n;
  std::scanf("%d", &n);
  std::vector<std::vector<Z<MOD>>> m(n, std::vector<Z<MOD>>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int v;
      std::scanf("%d", &v);
      m[i][j] = Z<MOD>(v);
    }
  }
  std::vector<Z<MOD>> p = get_charpoly(m);
  for (int i = 0; i <= n; ++i) {
    std::printf("%d", int(p[i].v_));
    if (i != n) std::printf(" ");
  }
  std::printf("\n");
  return 0;
}