#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

// clang-format off
template<unsigned Mod> class ModInt {
    static_assert((Mod >> 31) == 0, "`Mod` must less than 2^(31)");
    template<typename Int>
    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v) { using D = std::common_type_t<Int, unsigned>; return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v; }
    struct PrivateConstructor {} static inline private_constructor{};
    ModInt(PrivateConstructor, unsigned v) : v_(v) {}
    unsigned v_;

public:
    static unsigned mod() { return Mod; }
    static ModInt from_raw(unsigned v) { return ModInt(private_constructor, v); }
    static ModInt zero() { return from_raw(0); }
    static ModInt one() { return from_raw(1); }
    bool is_zero() const { return v_ == 0; }
    bool is_one() const { return v_ == 1; }
    ModInt() : v_() {}
    template<typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModInt(Int v) : v_(safe_mod(v)) {}
    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0> ModInt(Int v) : v_(v % Mod) {}
    unsigned val() const { return v_; }
    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_); }
    ModInt pow(long long e) const { if (e < 0) return inv().pow(-e); for (ModInt x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>= 1) == 0) return res; }}
    ModInt inv() const { int x1 = 1, x3 = 0, a = val(), b = Mod; while (b) { const int q = a / b, x1_old = x1, a_old = a; x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(x1 < 0 ? x1 + (int)Mod : x1); }
    template<bool Odd = (Mod & 1)> std::enable_if_t<Odd, ModInt> div_by_2() const { if (v_ & 1) return from_raw((v_ + Mod) >> 1); return from_raw(v_ >> 1); }
    ModInt &operator+=(const ModInt &a) { if ((v_ += a.v_) >= Mod) v_ -= Mod; return *this; }
    ModInt &operator-=(const ModInt &a) { if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod; return *this; }
    ModInt &operator*=(const ModInt &a) { v_ = (unsigned long long)v_ * a.v_ % Mod; return *this; }
    ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }
    ModInt &operator++() { return *this += one(); }
    ModInt operator++(int) { ModInt o(*this); *this += one(); return o; }
    ModInt &operator--() { return *this -= one(); }
    ModInt operator--(int) { ModInt o(*this); *this -= one(); return o; }
    friend ModInt operator+(const ModInt &a, const ModInt &b) { return ModInt(a) += b; }
    friend ModInt operator-(const ModInt &a, const ModInt &b) { return ModInt(a) -= b; }
    friend ModInt operator*(const ModInt &a, const ModInt &b) { return ModInt(a) *= b; }
    friend ModInt operator/(const ModInt &a, const ModInt &b) { return ModInt(a) /= b; }
    friend bool operator==(const ModInt &a, const ModInt &b) { return a.v_ == b.v_; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return a.v_ != b.v_; }
};
// clang-format on

template <typename Tp>
inline std::vector<Tp> batch_inv(const std::vector<Tp> &a) {
  if (a.empty())
    return {};
  const int n = a.size();
  std::vector<Tp> b(n);
  Tp v = 1;
  for (int i = 0; i < n; ++i)
    b[i] = v, v *= a[i];
  assert(v != 0);
  v = v.inv();
  for (int i = n - 1; i >= 0; --i)
    b[i] *= v, v *= a[i];
  return b;
}

template <typename Tp> class FftInfo {
  static Tp least_quadratic_nonresidue() {
    for (int i = 2;; ++i)
      if (Tp(i).pow((Tp::mod() - 1) / 2) == -1)
        return Tp(i);
  }

  const int ordlog2_;
  const Tp zeta_;
  const Tp invzeta_;
  const Tp imag_;
  const Tp invimag_;

  mutable std::vector<Tp> root_;
  mutable std::vector<Tp> invroot_;

  FftInfo()
      : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),
        zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >> ordlog2_)),
        invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_ - 2))),
        invimag_(-imag_), root_{Tp(1), imag_}, invroot_{Tp(1), invimag_} {}

public:
  static const FftInfo &get() {
    static FftInfo info;
    return info;
  }

  Tp imag() const { return imag_; }
  Tp inv_imag() const { return invimag_; }
  Tp zeta() const { return zeta_; }
  Tp inv_zeta() const { return invzeta_; }
  const std::vector<Tp> &root(int n) const {
    // [0, n)
    assert((n & (n - 1)) == 0);
    if (const int s = root_.size(); s < n) {
      root_.resize(n);
      for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {
        const int j = 1 << i;
        root_[j] = zeta_.pow(1LL << (ordlog2_ - i - 2));
        for (int k = j + 1; k < j * 2; ++k)
          root_[k] = root_[k - j] * root_[j];
      }
    }
    return root_;
  }
  const std::vector<Tp> &inv_root(int n) const {
    // [0, n)
    assert((n & (n - 1)) == 0);
    if (const int s = invroot_.size(); s < n) {
      invroot_.resize(n);
      for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {
        const int j = 1 << i;
        invroot_[j] = invzeta_.pow(1LL << (ordlog2_ - i - 2));
        for (int k = j + 1; k < j * 2; ++k)
          invroot_[k] = invroot_[k - j] * invroot_[j];
      }
    }
    return invroot_;
  }
};

inline int fft_len(int n) {
  --n;
  n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;
  return (n | n >> 16) + 1;
}

namespace detail {

template <typename Iterator>
inline void butterfly_n(
    Iterator a, int n,
    const std::vector<typename std::iterator_traits<Iterator>::value_type>
        &root) {
  assert(n > 0);
  assert((n & (n - 1)) == 0);
  const int bn = __builtin_ctz(n);
  if (bn & 1) {
    for (int i = 0; i < n / 2; ++i) {
      const auto a0 = a[i], a1 = a[i + n / 2];
      a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
    }
  }
  for (int i = n >> (bn & 1); i >= 4; i /= 4) {
    const int i4 = i / 4;
    for (int k = 0; k < i4; ++k) {
      const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
      const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
      const auto a02p = a0 + a2, a02m = a0 - a2;
      const auto a13p = a1 + a3, a13m = (a1 - a3) * root[1];
      a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
      a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
    }
    for (int j = i, m = 2; j < n; j += i, m += 2) {
      const auto r = root[m], r2 = r * r, r3 = r2 * r;
      for (int k = j; k < j + i4; ++k) {
        const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1] * r;
        const auto a2 = a[k + i4 * 2] * r2, a3 = a[k + i4 * 3] * r3;
        const auto a02p = a0 + a2, a02m = a0 - a2;
        const auto a13p = a1 + a3, a13m = (a1 - a3) * root[1];
        a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
        a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
      }
    }
  }
}

template <typename Iterator>
inline void inv_butterfly_n(
    Iterator a, int n,
    const std::vector<typename std::iterator_traits<Iterator>::value_type>
        &root) {
  assert(n > 0);
  assert((n & (n - 1)) == 0);
  const int bn = __builtin_ctz(n);
  for (int i = 4; i <= (n >> (bn & 1)); i *= 4) {
    const int i4 = i / 4;
    for (int k = 0; k < i4; ++k) {
      const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
      const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
      const auto a01p = a0 + a1, a01m = a0 - a1;
      const auto a23p = a2 + a3, a23m = (a2 - a3) * root[1];
      a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m + a23m;
      a[k + i4 * 2] = a01p - a23p, a[k + i4 * 3] = a01m - a23m;
    }
    for (int j = i, m = 2; j < n; j += i, m += 2) {
      const auto r = root[m], r2 = r * r, r3 = r2 * r;
      for (int k = j; k < j + i4; ++k) {
        const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
        const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
        const auto a01p = a0 + a1, a01m = a0 - a1;
        const auto a23p = a2 + a3, a23m = (a2 - a3) * root[1];
        a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = (a01m + a23m) * r;
        a[k + i4 * 2] = (a01p - a23p) * r2, a[k + i4 * 3] = (a01m - a23m) * r3;
      }
    }
  }
  if (bn & 1) {
    for (int i = 0; i < n / 2; ++i) {
      const auto a0 = a[i], a1 = a[i + n / 2];
      a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
    }
  }
}

} // namespace detail

// FFT_n: A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]
template <typename Iterator> inline void fft_n(Iterator a, int n) {
  using Tp = typename std::iterator_traits<Iterator>::value_type;
  detail::butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));
}

template <typename Tp> inline void fft(std::vector<Tp> &a) {
  fft_n(a.begin(), a.size());
}

// IFFT_n: bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |->
// A(x)
template <typename Iterator> inline void inv_fft_n(Iterator a, int n) {
  using Tp = typename std::iterator_traits<Iterator>::value_type;
  detail::inv_butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));
  const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;
  for (int i = 0; i < n; ++i)
    a[i] *= iv;
}

template <typename Tp> inline void inv_fft(std::vector<Tp> &a) {
  inv_fft_n(a.begin(), a.size());
}

// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))
template <typename Iterator>
inline void transposed_inv_fft_n(Iterator a, int n) {
  using Tp = typename std::iterator_traits<Iterator>::value_type;
  const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;
  for (int i = 0; i < n; ++i)
    a[i] *= iv;
  detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));
}

template <typename Tp> inline void transposed_inv_fft(std::vector<Tp> &a) {
  transposed_inv_fft_n(a.begin(), a.size());
}

// FFT_n^T : FFT_n((x^n A(x^(-1))) mod (x^n - 1)) |-> n A(x)
template <typename Iterator> inline void transposed_fft_n(Iterator a, int n) {
  using Tp = typename std::iterator_traits<Iterator>::value_type;
  detail::inv_butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));
}

template <typename Tp> inline void transposed_fft(std::vector<Tp> &a) {
  transposed_fft_n(a.begin(), a.size());
}

template <typename Tp>
inline std::vector<Tp> convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {
  if (a.empty() || b.empty())
    return {};
  const int n = a.size();
  const int m = b.size();
  const int len = fft_len(n + m - 1);
  a.resize(len);
  b.resize(len);
  fft(a);
  fft(b);
  for (int i = 0; i < len; ++i)
    a[i] *= b[i];
  inv_fft(a);
  a.resize(n + m - 1);
  return a;
}

template <typename Tp> inline std::vector<Tp> square_fft(std::vector<Tp> a) {
  if (a.empty())
    return {};
  const int n = a.size();
  const int len = fft_len(n * 2 - 1);
  a.resize(len);
  fft(a);
  for (int i = 0; i < len; ++i)
    a[i] *= a[i];
  inv_fft(a);
  a.resize(n * 2 - 1);
  return a;
}

template <typename Tp>
inline std::vector<Tp> convolution_naive(const std::vector<Tp> &a,
                                         const std::vector<Tp> &b) {
  if (a.empty() || b.empty())
    return {};
  const int n = a.size();
  const int m = b.size();
  std::vector<Tp> res(n + m - 1);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res[i + j] += a[i] * b[j];
  return res;
}

template <typename Tp>
inline std::vector<Tp> convolution(const std::vector<Tp> &a,
                                   const std::vector<Tp> &b) {
  if (std::min(a.size(), b.size()) < 60)
    return convolution_naive(a, b);
  if (std::addressof(a) == std::addressof(b))
    return square_fft(a);
  return convolution_fft(a, b);
}

template <typename Tp> class Binomial {
  std::vector<Tp> factorial_, invfactorial_;

  Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}

  void preprocess(int n) {
    if (const int nn = factorial_.size(); nn < n) {
      int k = nn;
      while (k < n)
        k *= 2;
      k = std::min<long long>(k, Tp::mod());
      factorial_.resize(k);
      invfactorial_.resize(k);
      for (int i = nn; i < k; ++i)
        factorial_[i] = factorial_[i - 1] * i;
      invfactorial_.back() = factorial_.back().inv();
      for (int i = k - 2; i >= nn; --i)
        invfactorial_[i] = invfactorial_[i + 1] * (i + 1);
    }
  }

public:
  static const Binomial &get(int n) {
    static Binomial bin;
    bin.preprocess(n);
    return bin;
  }

  Tp binom(int n, int m) const {
    return n < m ? Tp()
                 : factorial_[n] * invfactorial_[m] * invfactorial_[n - m];
  }
  Tp inv(int n) const { return factorial_[n - 1] * invfactorial_[n]; }
  Tp factorial(int n) const { return factorial_[n]; }
  Tp inv_factorial(int n) const { return invfactorial_[n]; }
};

template <typename Tp, typename Closure>
inline std::enable_if_t<
    std::is_invocable_r_v<Tp, Closure, int, const std::vector<Tp> &>,
    std::vector<Tp>>
semi_relaxed_convolution_naive(const std::vector<Tp> &A, Closure gen, int n) {
  std::vector<Tp> B(n), AB(n);
  for (int i = 0; i < n; ++i) {
    for (int j = std::max(0, i - (int)A.size() + 1); j < i; ++j)
      AB[i] += A[i - j] * B[j];
    B[i] = gen(i, AB);
    if (!A.empty())
      AB[i] += A[0] * B[i];
  }
  return B;
}

// returns coefficients generated by closure
// closure: gen(index, current_product)
template <typename Tp, typename Closure>
inline std::enable_if_t<
    std::is_invocable_r_v<Tp, Closure, int, const std::vector<Tp> &>,
    std::vector<Tp>>
semi_relaxed_convolution(const std::vector<Tp> &A, Closure gen, int n) {
  if (A.size() < 60)
    return semi_relaxed_convolution_naive(A, gen, n);
  enum { BaseCaseSize = 32 };
  static_assert((BaseCaseSize & (BaseCaseSize - 1)) == 0);

  static const int Block[] = {16, 16, 16, 16, 16};
  static const int BlockSize[] = {
      BaseCaseSize,
      BaseCaseSize * Block[0],
      BaseCaseSize * Block[0] * Block[1],
      BaseCaseSize * Block[0] * Block[1] * Block[2],
      BaseCaseSize * Block[0] * Block[1] * Block[2] * Block[3],
      BaseCaseSize * Block[0] * Block[1] * Block[2] * Block[3] * Block[4],
  };

  // returns (which_block, level)
  auto blockinfo = [](int ind) {
    int i = ind / BaseCaseSize, lv = 0;
    while ((i & (Block[lv] - 1)) == 0)
      i /= Block[lv++];
    return std::make_pair(i & (Block[lv] - 1), lv);
  };

  std::vector<Tp> B(n), AB(n);
  std::vector<std::vector<std::vector<Tp>>> dftA, dftB;

  for (int i = 0; i < n; ++i) {
    const int s = i & (BaseCaseSize - 1);

    // block contribution
    if (i >= BaseCaseSize && s == 0) {
      const auto [j, lv] = blockinfo(i);
      const int blocksize = BlockSize[lv];

      if (blocksize * j == i) {
        if ((int)dftA.size() == lv) {
          dftA.emplace_back();
          dftB.emplace_back(Block[lv] - 1);
        }
        if ((j - 1) * blocksize < (int)A.size()) {
          dftA[lv]
              .emplace_back(A.begin() + (j - 1) * blocksize,
                            A.begin() +
                                std::min<int>((j + 1) * blocksize, A.size()))
              .resize(blocksize * 2);
          fft(dftA[lv][j - 1]);
        }
      }

      if (!dftA[lv].empty()) {
        dftB[lv][j - 1].resize(blocksize * 2);
        std::copy_n(B.begin() + (i - blocksize), blocksize,
                    dftB[lv][j - 1].begin());
        std::fill_n(dftB[lv][j - 1].begin() + blocksize, blocksize, Tp(0));
        fft(dftB[lv][j - 1]);

        // middle product
        std::vector<Tp> mp(blocksize * 2);
        for (int k = 0; k < std::min<int>(j, dftA[lv].size()); ++k)
          for (int l = 0; l < blocksize * 2; ++l)
            mp[l] += dftA[lv][k][l] * dftB[lv][j - 1 - k][l];
        inv_fft(mp);

        for (int k = 0; k < blocksize && i + k < n; ++k)
          AB[i + k] += mp[k + blocksize];
      }
    }

    // basecase contribution
    for (int j = std::max(i - s, i - (int)A.size() + 1); j < i; ++j)
      AB[i] += A[i - j] * B[j];
    B[i] = gen(i, AB);
    if (!A.empty())
      AB[i] += A[0] * B[i];
  }

  return B;
}
#line 8 "fps_basic.hpp"

template <typename Tp> inline int order(const std::vector<Tp> &a) {
  for (int i = 0; i < (int)a.size(); ++i)
    if (a[i] != 0)
      return i;
  return -1;
}

template <typename Tp>
inline std::vector<Tp> fps_inv(const std::vector<Tp> &a, int n) {
  assert(order(a) == 0);
  if (n <= 0)
    return {};
  if (std::min<int>(a.size(), n) < 60)
    return semi_relaxed_convolution(
        a, [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n] * v; },
        n);
  enum { Threshold = 32 };
  const int len = fft_len(n);
  std::vector<Tp> invA, shopA(len), shopB(len);
  invA = semi_relaxed_convolution(
      a, [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n] * v; },
      Threshold);
  invA.resize(len);
  for (int i = Threshold * 2; i <= len; i *= 2) {
    std::fill(std::copy_n(a.begin(), std::min<int>(a.size(), i), shopA.begin()),
              shopA.begin() + i, Tp(0));
    std::copy_n(invA.begin(), i, shopB.begin());
    fft_n(shopA.begin(), i);
    fft_n(shopB.begin(), i);
    for (int j = 0; j < i; ++j)
      shopA[j] *= shopB[j];
    inv_fft_n(shopA.begin(), i);
    std::fill_n(shopA.begin(), i / 2, Tp(0));
    fft_n(shopA.begin(), i);
    for (int j = 0; j < i; ++j)
      shopA[j] *= shopB[j];
    inv_fft_n(shopA.begin(), i);
    for (int j = i / 2; j < i; ++j)
      invA[j] = -shopA[j];
  }
  invA.resize(n);
  return invA;
}

template <typename Tp>
inline std::vector<Tp> fps_div(const std::vector<Tp> &a,
                               const std::vector<Tp> &b, int n) {
  assert(order(b) == 0);
  if (n <= 0)
    return {};
  return semi_relaxed_convolution(
      b,
      [&, v = b[0].inv()](int n, auto &&c) {
        if (n < (int)a.size())
          return (a[n] - c[n]) * v;
        return -c[n] * v;
      },
      n);
}

template <typename Tp> inline std::vector<Tp> deriv(const std::vector<Tp> &a) {
  const int n = (int)a.size() - 1;
  if (n <= 0)
    return {};
  std::vector<Tp> res(n);
  for (int i = 1; i <= n; ++i)
    res[i - 1] = a[i] * i;
  return res;
}

template <typename Tp>
inline std::vector<Tp> integr(const std::vector<Tp> &a, Tp c = {}) {
  const int n = a.size() + 1;
  auto &&bin = Binomial<Tp>::get(n);
  std::vector<Tp> res(n);
  res[0] = c;
  for (int i = 1; i < n; ++i)
    res[i] = a[i - 1] * bin.inv(i);
  return res;
}

template <typename Tp> inline int degree(const std::vector<Tp> &a) {
  int n = (int)a.size() - 1;
  while (n >= 0 && a[n] == 0)
    --n;
  return n;
}

template <typename Tp> inline void shrink(std::vector<Tp> &a) {
  a.resize(degree(a) + 1);
}

template <typename Tp> class SubproductTree {
public:
  // LV=0   => T[0..S]  = DFT((x-X_0)..(x-X_(N-1))     mod (x^S     - 1))
  //        => T[S..2S] = (x-X_0)..(x-X_(N-1))         mod (x^S     + 1)  (*
  //        SPECIAL CASE)
  // LV=1   => T[..]    = DFT((x-X_0)..(x-X_(S/2-1))   mod (x^(S/2) - 1))
  //        => T[..]    = DFT((x-X_(S/2))..(x-X_(N-1)) mod (x^(S/2) - 1)) (*
  //        GENERAL CASE)
  // LV=2.. => ..                                                         (*
  // GENERAL CASE)
  std::vector<Tp> T;
  int N;
  int S;

  explicit SubproductTree(const std::vector<Tp> &X)
      : N(X.size()), S(N == 0 ? 2 : std::max(fft_len(N), 2)) {
    int LogS = 1;
    while ((1 << LogS) < S)
      ++LogS;
    T.assign((LogS + 1) * S * 2, 1);
    for (int i = 0; i < N; ++i) {
      T[LogS * S * 2 + i * 2] = 1 - X[i];
      T[LogS * S * 2 + i * 2 + 1] = -1 - X[i];
    }
    for (int lv = LogS - 1, len = 2; lv >= 0; --lv, len *= 2) {
      const auto t = FftInfo<Tp>::get().root(len).at(len / 2);
      for (int i = 0; i < (1 << lv); ++i) {
        auto C = T.begin() + (lv * S * 2 + i * len * 2);       // current
        auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
        for (int j = 0; j < len; ++j)
          C[j] = C[len + j] = L[j] * L[len + j];
        inv_fft_n(C + len, len);
        if ((i + 1) * len <= N)
          C[len] -= 2;
        if (lv) {
          Tp k = 1;
          for (int j = 0; j < len; ++j)
            C[len + j] *= k, k *= t;
          fft_n(C + len, len);
        }
      }
    }
  }

  std::vector<Tp> product() const {
    std::vector res(T.begin() + S, T.begin() + S * 2);
    if (N == S) {
      res[0] += 1;
      res.emplace_back(1);
    }
    res.resize(N + 1);
    return res;
  }

  // see:
  // [1]: A. Bostan, Grégoire Lecerf, É. Schost. Tellegen's principle into
  // practice. [2]: D. Bernstein. SCALED REMAINDER TREES.
  std::vector<Tp> evaluation(const std::vector<Tp> &F) const {
    const int degF = degree(F);
    const auto P = product();
    // find coefficients of x^(-1),...,x^(-N) of F/P in R((x^(-1)))
    auto res = fps_div(std::vector(F.rend() - (degF + 1), F.rend()),
                       std::vector(P.rbegin(), P.rend()), degF + 1);
    if (degF >= N)
      res.erase(res.begin(), res.begin() + (degF - N + 1));
    std::reverse(res.begin(), res.end());
    res.resize(N);
    res.insert(res.begin(), S - N,
               Tp(0)); // res[S-1]=[x^(-1)]F/P, res[S-2]=[x^(-2)]F/P, ...
    fft(res);
    for (int lv = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {
      const auto t = FftInfo<Tp>::get().inv_root(len / 2).at(len / 4);
      std::vector<Tp> LL(len);
      for (int i = 0; i < (1 << lv); ++i) {
        auto C = res.begin() + i * len;                        // current
        auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
        for (int j = 0; j < len; ++j)
          LL[j] = C[j] * L[len + j], C[j] *= L[j];
        // extract the higher part of DFT array
        inv_fft_n(LL.begin() + len / 2, len / 2);
        inv_fft_n(C + len / 2, len / 2);
        Tp k = 1;
        for (int j = 0; j < len / 2; ++j) {
          LL[j + len / 2] *= k, C[j + len / 2] *= k;
          k *= t;
        }
        fft_n(LL.begin() + len / 2, len / 2);
        fft_n(C + len / 2, len / 2);
        for (int j = 0; j < len / 2; ++j) {
          C[j + len / 2] = (C[j] - C[j + len / 2]).div_by_2();
          C[j] = (LL[j] - LL[j + len / 2]).div_by_2();
        }
      }
    }
    res.resize(N);
    return res;
  }

  std::vector<Tp> interpolation(const std::vector<Tp> &Y) const {
    assert((int)Y.size() == N);
    const auto invD =
        batch_inv(evaluation(deriv(product()))); // denominator => P'(x_i)
    std::vector<Tp> res(S * 2);
    for (int i = 0; i < N; ++i)
      res[i * 2] = res[i * 2 + 1] = Y[i] * invD[i];
    int LogS = 1;
    while ((1 << LogS) < S)
      ++LogS;
    for (int lv = LogS - 1, len = 2; lv >= 0; --lv, len *= 2) {
      const auto t = FftInfo<Tp>::get().root(len).at(len / 2);
      for (int i = 0; i < (1 << lv); ++i) {
        auto C = res.begin() + i * len * 2;                    // current
        auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
        for (int j = 0; j < len; ++j)
          C[j] = C[len + j] = C[j] * L[len + j] + C[len + j] * L[j];
        inv_fft_n(C + len, len);
        if (lv) {
          Tp k = 1;
          for (int j = 0; j < len; ++j)
            C[len + j] *= k, k *= t;
          fft_n(C + len, len);
        }
      }
    }
    return std::vector(res.begin() + S, res.begin() + (S + N));
  }
};

int main() {
  using mint = ModInt<998244353>;

  int n;
  std::scanf("%d", &n);
  assert(n > 0);

  std::vector<mint> f(n);
  for (int i = 0; i < n; ++i) {
    unsigned v;
    std::scanf("%u", &v);
    f[i] = v;
  }

  std::vector<mint> xs(n + 1);
  for (int i = 0; i <= n; ++i)
    xs[i] = i;
  const SubproductTree<mint> t(xs);

  std::vector<mint> ys = t.evaluation(f);
  ys.pop_back();
  ys.insert(ys.begin(), mint(0));
  for (int i = 1; i <= n; ++i)
    ys[i] += ys[i - 1];

  const std::vector<mint> g = t.interpolation(ys);

  for (int i = 0; i <= n; ++i) {
    if (i)
      std::printf(" ");
    std::printf("%u", g[i].val());
  }
  std::puts("");

  return 0;
}
