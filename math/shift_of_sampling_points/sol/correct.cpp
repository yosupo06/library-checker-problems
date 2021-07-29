#include <algorithm>
#include <cassert>
#include <cstdio>
#include <functional>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;

template <u32 mod>
struct Z {

  static_assert(mod > 1);
  static_assert(mod < (1U << 31));

  u32 v_;

  Z() = default;
  Z(u32 v) : v_(v % mod) {}
  Z(int v) : v_((v % int(mod) + int(mod)) % mod) {}
  Z(const Z &) = default;
  ~Z()         = default;

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

template <u32 mod, u32 primitive_root>
struct NTT {
  static int deBruijn_log2(u64 n) {
    static constexpr u64 deBruijn    = 0x022fdd63cc95386d;
    static constexpr int convert[64] = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
        22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
        23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};
    return convert[n * deBruijn >> 58];
  }

  static int bsr(u64 n) { return deBruijn_log2(n & ~(n - 1)); }

  NTT() : dw_(bsr(mod - 1)), idw_(bsr(mod - 1)) {
    int lv = bsr(mod - 1);
    Z<mod> g(primitive_root);                        // any quadratic nonresidue is okay
    std::vector<Z<mod>> root(lv - 1), iroot(lv - 1); // order(`root[i]`) = 2^(`i` + 2)
    root.back() = g.pow((mod - 1) >> lv);
    for (int i = lv - 3; i >= 0; --i) root[i] = root[i + 1] * root[i + 1];
    iroot.back() = root.back().inv();
    for (int i = lv - 3; i >= 0; --i) iroot[i] = iroot[i + 1] * iroot[i + 1];
    Z<mod> v(1);
    for (int i = 0; i < lv - 2; ++i) dw_[i] = v * root[i], v *= iroot[i];
    v = Z<mod>(1);
    for (int i = 0; i < lv - 2; ++i) idw_[i] = v * iroot[i], v *= root[i];
  }
  ~NTT() = default;

  void dft(std::vector<Z<mod>> &x) const {
    int n = x.size();
    assert((n & (n - 1)) == 0);
    for (int j = 0, l = n >> 1; j != l; ++j) {
      Z<mod> u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int i = n >> 1; i >= 2; i >>= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        Z<mod> u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      Z<mod> root(dw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = 0; k != l; ++k) {
          Z<mod> u = x[j + k], v = x[j + k + l] * root;
          x[j + k] = u + v, x[j + k + l] = u - v;
        }
        root *= dw_[bsr(++m)];
      }
    }
  }
  void idft(std::vector<Z<mod>> &x) const {
    int n = x.size();
    assert((n & (n - 1)) == 0);
    for (int i = 2; i < n; i <<= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        Z<mod> u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      Z<mod> root(idw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = 0; k != l; ++k) {
          Z<mod> u = x[j + k], v = x[j + k + l];
          x[j + k] = u + v, x[j + k + l] = (u - v) * root;
        }
        root *= idw_[bsr(++m)];
      }
    }
    Z<mod> iv(Z<mod>(n).inv());
    for (int j = 0, l = n >> 1; j != l; ++j) {
      Z<mod> u = x[j] * iv, v = x[j + l] * iv;
      x[j] = u + v, x[j + l] = u - v;
    }
  }

  std::vector<Z<mod>> dw_, idw_;
};

template <u32 mod, u32 pr>
std::vector<Z<mod>> mult(const std::vector<Z<mod>> &x, const std::vector<Z<mod>> &y,
                         const NTT<mod, pr> &ntt) {
  int n = x.size(), m = y.size();
  assert(n > 0);
  assert(m > 0);
  int ntt_len = 1;
  int res_len = n + m - 1;
  while (ntt_len < res_len) ntt_len <<= 1;
  std::vector<Z<mod>> x_copy(x), y_copy(y);
  x_copy.resize(ntt_len, Z<mod>(0));
  y_copy.resize(ntt_len, Z<mod>(0));
  ntt.dft(x_copy);
  ntt.dft(y_copy);
  for (int i = 0; i < ntt_len; ++i) x_copy[i] *= y_copy[i];
  ntt.idft(x_copy);
  x_copy.resize(res_len);
  return x_copy;
}

template <u32 mod>
struct FactorialModPrime {
  FactorialModPrime(int n = 1) : fact_(n), ifact_(n) {
    assert(n > 0);
    assert(n < int(mod));
    fact_[0]  = Z<mod>(1);
    ifact_[0] = Z<mod>(1);
    for (int i = 1; i < n; ++i) fact_[i] = fact_[i - 1] * Z<mod>(i);
    ifact_.back() = fact_.back().inv();
    for (int i = n - 2; i >= 1; --i) ifact_[i] = ifact_[i + 1] * Z<mod>(i + 1);
  }
  ~FactorialModPrime() = default;
  void preprocess(int n) {
    if (int(fact_.size()) < n) {
      int old_size = fact_.size();
      fact_.resize(n);
      ifact_.resize(n);
      for (int i = old_size; i < n; ++i) fact_[i] = fact_[i - 1] * Z<mod>(i);
      ifact_.back() = fact_.back().inv();
      for (int i = n - 2; i >= old_size; --i) ifact_[i] = ifact_[i + 1] * Z<mod>(i + 1);
    }
  }
  Z<mod> get_fact(int n) const { return fact_[n]; }
  Z<mod> get_ifact(int n) const { return ifact_[n]; }

  std::vector<Z<mod>> fact_, ifact_;
};

template <u32 mod, typename ConvolveFuncType>
std::vector<Z<mod>> sample_points_to_FFP(const std::vector<Z<mod>> &pts,
                                         FactorialModPrime<mod> &fmp, ConvolveFuncType convolve) {
  // FFP is falling factorial polynomial
  int n = pts.size();
  std::vector<Z<mod>> emx(n), pts_egf(n); // `emx` = e^(-x), `pts_egf` = sample points' EGF
  fmp.preprocess(n);
  for (int i = 0; i < n; ++i) {
    pts_egf[i] = pts[i] * fmp.get_ifact(i);
    if (i & 1) emx[i] = -fmp.get_ifact(i);
    else
      emx[i] = fmp.get_ifact(i);
  }
  pts_egf = convolve(emx, pts_egf);
  pts_egf.resize(n);
  return pts_egf;
}

template <u32 mod, typename ConvolveFuncType>
std::vector<Z<mod>> FFP_to_sample_points(int n, const std::vector<Z<mod>> &ffp,
                                         FactorialModPrime<mod> &fmp, ConvolveFuncType convolve) {
  fmp.preprocess(n);
  std::vector<Z<mod>> ex(n); // `ex` = e^(x)
  for (int i = 0; i < n; ++i) ex[i] = fmp.get_ifact(i);
  if (int(ffp.size()) > n) ex = convolve(ex, std::vector<Z<mod>>(ffp.begin(), ffp.begin() + n));
  else
    ex = convolve(ex, ffp);
  ex.resize(n);
  for (int i = 0; i < n; ++i) ex[i] *= fmp.get_fact(i);
  return ex;
}

template <u32 mod, typename ConvolveFuncType>
std::vector<Z<mod>> shift_FFP(const std::vector<Z<mod>> &ffp, Z<mod> c, FactorialModPrime<mod> &fmp,
                              ConvolveFuncType convolve) {
  int n = ffp.size();
  fmp.preprocess(n);
  std::vector<Z<mod>> A(ffp), B(n);
  Z<mod> c_i(1);
  for (int i = 0; i < n; ++i)
    A[i] *= fmp.get_fact(i), B[i] = c_i * fmp.get_ifact(i), c_i *= c - Z<mod>(i);
  std::reverse(A.begin(), A.end());
  A = convolve(A, B);
  A.resize(n);
  std::reverse(A.begin(), A.end());
  for (int i = 0; i < n; ++i) A[i] *= fmp.get_ifact(i);
  return A;
}

int main() {
  int n, m, c;
  std::scanf("%d %d %d", &n, &m, &c);

  const u32 MOD = 998244353;
  const u32 PR  = 3;
  using mint    = Z<MOD>;
  NTT<MOD, PR> ntt998244353;
  FactorialModPrime<MOD> fmp998244353;

  auto conv = std::bind(mult<MOD, PR>, std::placeholders::_1, std::placeholders::_2,
                        std::cref(ntt998244353));

  std::vector<mint> pts(n);
  for (int i = 0; i < n; ++i) {
    int v;
    std::scanf("%d", &v);
    pts[i] = mint(v);
  }

  auto ffp = sample_points_to_FFP<MOD, decltype(conv)>(pts, fmp998244353, conv);
  ffp      = shift_FFP<MOD, decltype(conv)>(ffp, mint(c), fmp998244353, conv);
  auto res = FFP_to_sample_points<MOD, decltype(conv)>(m, ffp, fmp998244353, conv);

  for (int i = 0; i < m; ++i) {
    std::printf("%d", int(res[i].v_));
    if (i != m - 1) std::printf(" ");
  }
  std::printf("\n");
  return 0;
}