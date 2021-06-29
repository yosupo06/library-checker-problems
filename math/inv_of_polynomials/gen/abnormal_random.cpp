#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <vector>

#include "../params.h"
#include "random.h"

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

template <typename ModType>
std::vector<ModType> poly_mul(const std::vector<ModType> &x, const std::vector<ModType> &y) {
  int n = x.size(), m = y.size();
  std::vector<ModType> res(n + m - 1, ModType(0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      res[i + j] += x[i] * y[j];
    }
  }
  return res;
}

template <typename ModType>
std::vector<ModType> poly_add(const std::vector<ModType> &x, const std::vector<ModType> &y) {
  std::vector<ModType> res(x);
  if (res.size() < y.size()) res.resize(y.size(), ModType(0));
  for (int i = 0, ie = y.size(); i < ie; ++i) res[i] += y[i];
  return res;
}

template <typename ModType> int get_poly_deg_and_shrink(std::vector<ModType> &x) {
  while (!x.empty() && x.back() == ModType(0)) x.pop_back();
  if (x.empty()) x.push_back(ModType(0));
  return (x.size() == 1 && x[0] == ModType(0)) ? -1 : int(x.size()) - 1;
}

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int DEG_MAX = 1000;
  const int REMAINDER_SEQUENCE_DIFF_MAX = 20;

  using mint = Z<u32(MOD)>;

  auto rand_poly = [&gen] (int deg) {
    std::vector<mint> res(deg + 1);
    for (auto &i : res) i = gen.uniform<int>(1, MOD - 1);
    return res;
  };

  std::vector<mint> a{mint(0)}, b{mint(1)};

  while (get_poly_deg_and_shrink(b) < DEG_MAX - REMAINDER_SEQUENCE_DIFF_MAX) {
    // (a + b * r, b) <- (b, a)
    std::vector<mint> tmp_b(b);
    b = poly_add(a, poly_mul(b, rand_poly(gen.uniform<int>(1, REMAINDER_SEQUENCE_DIFF_MAX))));
    a = tmp_b;
  }

  if (gen.uniform_bool()) std::swap(a, b);

  int n = a.size(), m = b.size();

  std::printf("%d %d\n", n, m);

  for (int i = 0; i < n; ++i) {
    std::printf("%d", int(a[i].v_));
    if (i != n - 1) std::printf(" ");
  }
  std::printf("\n");
  for (int i = 0; i < m; ++i) {
    std::printf("%d", int(b[i].v_));
    if (i != m - 1) std::printf(" ");
  }
  std::printf("\n");
  return 0;
}
