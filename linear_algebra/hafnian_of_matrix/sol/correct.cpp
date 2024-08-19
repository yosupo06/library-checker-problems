#include <cstdint>

template <std::uint_fast64_t mod> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 v;

  constexpr modint(const u64 x = 0) noexcept : v(x % mod) {}
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    v += rhs.v;
    if (v >= mod)
      v -= mod;
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (v < rhs.v)
      v += mod;
    v -= rhs.v;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    v = v * rhs.v % mod;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = mod - 2;
    while (exp != 0) {
      if (exp % 2 != 0)
        *this *= rhs;
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};

#include <cstddef>
#include <utility>
#include <vector>

template <class T> class hafnian_impl {
  using size_t = std::size_t;
  template <class U> using vec = std::vector<U>;
  using poly = vec<T>;

  size_t deg;

  void aa_mul_shl(poly &c, const poly &a, const poly &b) const {
    for (size_t i = 0; i != deg; ++i) {
      for (size_t j = 0; i + j + 1 != deg; ++j) {
        c[i + j + 1] += a[i] * b[j];
      }
    }
  }

  poly f(vec<vec<poly>> b) const {
    if (b.empty()) {
      poly ret(deg, 0);
      ret[0] = 1;
      return ret;
    }

    const auto x = std::move(b.back());
    b.pop_back();
    const auto y = std::move(b.back());
    b.pop_back();
    const size_t n = b.size();

    poly ret(deg, 0);

    {
      const poly zero = f(b);
      for (size_t i = 0; i != deg; ++i) {
        ret[i] -= zero[i];
      }
    }
    for (size_t i = 0; i != n; ++i) {
      for (size_t j = 0; j != i; ++j) {
        aa_mul_shl(b[i][j], x[i], y[j]);
        aa_mul_shl(b[i][j], y[i], x[j]);
      }
    }
    {
      const poly all = f(std::move(b));
      aa_mul_shl(ret, x[n], all);
      for (size_t i = 0; i != deg; ++i) {
        ret[i] += all[i];
      }
    }
    return ret;
  }

public:
  hafnian_impl(const size_t deg) : deg(deg) {}

  T operator()(const vec<vec<T>> &a) const {
    const size_t n = a.size();
    vec<vec<poly>> b(n);
    for (size_t i = 0; i != n; ++i) {
      b[i] = vec<poly>(i, poly(deg, T(0)));
      for (size_t j = 0; j != i; ++j) {
        b[i][j][0] = a[i][j];
      }
    }
    return f(std::move(b)).back();
  }
};

template <class T> T hafnian(const std::vector<std::vector<T>> &a) {
  hafnian_impl<T> impl(a.size() / 2 + 1);
  return impl(a);
}

#include <cstdio>

int main() {
  using mint = modint<998244353>;

  int n;
  std::scanf("%d", &n);

  std::vector<std::vector<mint>> a(n, std::vector<mint>(n));
  for (auto &v : a) {
    for (auto &e : v) {
      int a_;
      std::scanf("%d", &a_);
      e.v = a_;
    }
  }

  const auto ans = hafnian(a);

  std::printf("%d\n", static_cast<int>(ans.v));
  return 0;
}
