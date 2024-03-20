#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  
  constexpr mint inverse() const { return pow(mod - 2); }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }
  
  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};
template <typename mint>
struct NTT {
  static constexpr uint32_t get_pr() {
    uint32_t _mod = mint::get_mod();
    using u64 = uint64_t;
    u64 ds[32] = {};
    int idx = 0;
    u64 m = _mod - 1;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        ds[idx++] = i;
        while (m % i == 0) m /= i;
      }
    }
    if (m != 1) ds[idx++] = m;

    uint32_t _pr = 2;
    while (1) {
      int flg = 1;
      for (int i = 0; i < idx; ++i) {
        u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
        while (b) {
          if (b & 1) r = r * a % _mod;
          a = a * a % _mod;
          b >>= 1;
        }
        if (r == 1) {
          flg = 0;
          break;
        }
      }
      if (flg == 1) break;
      ++_pr;
    }
    return _pr;
  };

  static constexpr uint32_t mod = mint::get_mod();
  static constexpr uint32_t pr = get_pr();
  static constexpr int level = __builtin_ctzll(mod - 1);
  mint dw[level], dy[level];

  void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inverse();
    for (int i = k - 2; i > 0; --i)
      w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
    dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
    for (int i = 3; i < k; ++i) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  NTT() { setwy(level); }

  void fft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if (k & 1) {
      int v = 1 << (k - 1);
      for (int j = 0; j < v; ++j) {
        mint ajv = a[j + v];
        a[j + v] = a[j] - ajv;
        a[j] += ajv;
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    mint one = mint(1);
    mint imag = dw[1];
    while (v) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = j1 + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dw[2], wx = one;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, wx = ww * xx;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww,
               t3 = a[j2 + v] * wx;
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j0 + v] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j2 + v] = t0m2 - t1m3;
        }
        xx *= dw[__builtin_ctzll((jh += 4))];
      }
      u <<= 2;
      v >>= 2;
    }
  }

  void ifft4(vector<mint> &a, int k) {
    if ((int)a.size() <= 1) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    mint one = mint(1);
    mint imag = dy[1];
    while (u) {
      // jh = 0
      {
        int j0 = 0;
        int j1 = v;
        int j2 = v + v;
        int j3 = j2 + v;
        for (; j0 < v; ++j0, ++j1, ++j2, ++j3) {
          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;
          a[j0] = t0p1 + t2p3, a[j2] = t0p1 - t2p3;
          a[j1] = t0m1 + t2m3, a[j3] = t0m1 - t2m3;
        }
      }
      // jh >= 1
      mint ww = one, xx = one * dy[2], yy = one;
      u <<= 2;
      for (int jh = 4; jh < u;) {
        ww = xx * xx, yy = xx * imag;
        int j0 = jh * v;
        int je = j0 + v;
        int j2 = je + v;
        for (; j0 < je; ++j0, ++j2) {
          mint t0 = a[j0], t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;
          a[j0 + v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;
        }
        xx *= dy[__builtin_ctzll(jh += 4)];
      }
      u >>= 4;
      v <<= 2;
    }
    if (k & 1) {
      u = 1 << (k - 1);
      for (int j = 0; j < u; ++j) {
        mint ajv = a[j] - a[j + u];
        a[j] += a[j + u];
        a[j + u] = ajv;
      }
    }
  }

  void ntt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    fft4(a, __builtin_ctz(a.size()));
  }

  void intt(vector<mint> &a) {
    if ((int)a.size() <= 1) return;
    ifft4(a, __builtin_ctz(a.size()));
    mint iv = mint(a.size()).inverse();
    for (auto &x : a) x *= iv;
  }

  vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
    int l = a.size() + b.size() - 1;
    if (min<int>(a.size(), b.size()) <= 40) {
      vector<mint> s(l);
      for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
      return s;
    }
    int k = 2, M = 4;
    while (M < l) M <<= 1, ++k;
    setwy(k);
    vector<mint> s(M), t(M);
    for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i];
    for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i];
    fft4(s, k);
    fft4(t, k);
    for (int i = 0; i < M; ++i) s[i] *= t[i];
    ifft4(s, k);
    s.resize(l);
    mint invm = mint(M).inverse();
    for (int i = 0; i < l; ++i) s[i] *= invm;
    return s;
  }

  void ntt_doubling(vector<mint> &a) {
    int M = (int)a.size();
    auto b = a;
    intt(b);
    mint r = 1, zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
    for (int i = 0; i < M; i++) b[i] *= r, r *= zeta;
    ntt(b);
    copy(begin(b), end(b), back_inserter(a));
  }
};

namespace ArbitraryNTT {
using i64 = int64_t;
using u128 = __uint128_t;
constexpr int32_t m0 = 167772161;
constexpr int32_t m1 = 469762049;
constexpr int32_t m2 = 754974721;
using mint0 = LazyMontgomeryModInt<m0>;
using mint1 = LazyMontgomeryModInt<m1>;
using mint2 = LazyMontgomeryModInt<m2>;
constexpr int r01 = mint1(m0).inverse().get();
constexpr int r02 = mint2(m0).inverse().get();
constexpr int r12 = mint2(m1).inverse().get();
constexpr int r02r12 = i64(r02) * r12 % m2;
constexpr i64 w1 = m0;
constexpr i64 w2 = i64(m0) * m1;

template <typename T, typename submint>
vector<submint> mul(const vector<T> &a, const vector<T> &b) {
  static NTT<submint> ntt;
  vector<submint> s(a.size()), t(b.size());
  for (int i = 0; i < (int)a.size(); ++i) s[i] = i64(a[i] % submint::get_mod());
  for (int i = 0; i < (int)b.size(); ++i) t[i] = i64(b[i] % submint::get_mod());
  return ntt.multiply(s, t);
}

template <typename T>
vector<int> multiply(const vector<T> &s, const vector<T> &t, int mod) {
  auto d0 = mul<T, mint0>(s, t);
  auto d1 = mul<T, mint1>(s, t);
  auto d2 = mul<T, mint2>(s, t);
  int n = d0.size();
  vector<int> ret(n);
  const int W1 = w1 % mod;
  const int W2 = w2 % mod;
  for (int i = 0; i < n; i++) {
    int n1 = d1[i].get(), n2 = d2[i].get(), a = d0[i].get();
    int b = i64(n1 + m1 - a) * r01 % m1;
    int c = (i64(n2 + m2 - a) * r02r12 + i64(m2 - b) * r12) % m2;
    ret[i] = (i64(a) + i64(b) * W1 + i64(c) * W2) % mod;
  }
  return ret;
}

template <typename mint>
vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
  if (a.size() == 0 && b.size() == 0) return {};
  if (min<int>(a.size(), b.size()) < 128) {
    vector<mint> ret(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); ++i)
      for (int j = 0; j < (int)b.size(); ++j) ret[i + j] += a[i] * b[j];
    return ret;
  }
  vector<int> s(a.size()), t(b.size());
  for (int i = 0; i < (int)a.size(); ++i) s[i] = a[i].get();
  for (int i = 0; i < (int)b.size(); ++i) t[i] = b[i].get();
  vector<int> u = multiply<int>(s, t, mint::get_mod());
  vector<mint> ret(u.size());
  for (int i = 0; i < (int)u.size(); ++i) ret[i] = mint(u[i]);
  return ret;
}

template <typename T>
vector<u128> multiply_u128(const vector<T> &s, const vector<T> &t) {
  if (s.size() == 0 && t.size() == 0) return {};
  if (min<int>(s.size(), t.size()) < 128) {
    vector<u128> ret(s.size() + t.size() - 1);
    for (int i = 0; i < (int)s.size(); ++i)
      for (int j = 0; j < (int)t.size(); ++j) ret[i + j] += i64(s[i]) * t[j];
    return ret;
  }
  auto d0 = mul<T, mint0>(s, t);
  auto d1 = mul<T, mint1>(s, t);
  auto d2 = mul<T, mint2>(s, t);
  int n = d0.size();
  vector<u128> ret(n);
  for (int i = 0; i < n; i++) {
    i64 n1 = d1[i].get(), n2 = d2[i].get();
    i64 a = d0[i].get();
    i64 b = (n1 + m1 - a) * r01 % m1;
    i64 c = ((n2 + m2 - a) * r02r12 + (m2 - b) * r12) % m2;
    ret[i] = a + b * w1 + u128(c) * w2;
  }
  return ret;
}
}  // namespace ArbitraryNTT

namespace MultiPrecisionIntegerImpl {
struct TENS {
  static constexpr int offset = 30;
  constexpr TENS() : _tend() {
    _tend[offset] = 1;
    for (int i = 1; i <= offset; i++) {
      _tend[offset + i] = _tend[offset + i - 1] * 10.0;
      _tend[offset - i] = 1.0 / _tend[offset + i];
    }
  }
  long double ten_ld(int n) const {
    assert(-offset <= n and n <= offset);
    return _tend[n + offset];
  }

 private:
  long double _tend[offset * 2 + 1];
};
}  // namespace MultiPrecisionIntegerImpl

// 0 は neg=false, dat={} として扱う
struct MultiPrecisionInteger {
  using M = MultiPrecisionInteger;
  inline constexpr static MultiPrecisionIntegerImpl::TENS tens = {};

  static constexpr int D = 1000000000;
  static constexpr int logD = 9;
  bool neg;
  vector<int> dat;

  MultiPrecisionInteger() : neg(false), dat() {}

  MultiPrecisionInteger(bool n, const vector<int>& d) : neg(n), dat(d) {}

  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>>* = nullptr>
  MultiPrecisionInteger(I x) : neg(false) {
    if constexpr (is_signed_v<I> || is_same_v<I, __int128_t>) {
      if (x < 0) neg = true, x = -x;
    }
    while (x) dat.push_back(x % D), x /= D;
  }

  MultiPrecisionInteger(const string& S) : neg(false) {
    assert(!S.empty());
    if (S.size() == 1u && S[0] == '0') return;
    int l = 0;
    if (S[0] == '-') ++l, neg = true;
    for (int ie = S.size(); l < ie; ie -= logD) {
      int is = max(l, ie - logD);
      long long x = 0;
      for (int i = is; i < ie; i++) x = x * 10 + S[i] - '0';
      dat.push_back(x);
    }
  }

  friend M operator+(const M& lhs, const M& rhs) {
    if (lhs.neg == rhs.neg) return {lhs.neg, _add(lhs.dat, rhs.dat)};
    if (_leq(lhs.dat, rhs.dat)) {
      // |l| <= |r|
      auto c = _sub(rhs.dat, lhs.dat);
      bool n = _is_zero(c) ? false : rhs.neg;
      return {n, c};
    }
    auto c = _sub(lhs.dat, rhs.dat);
    bool n = _is_zero(c) ? false : lhs.neg;
    return {n, c};
  }
  friend M operator-(const M& lhs, const M& rhs) { return lhs + (-rhs); }

  friend M operator*(const M& lhs, const M& rhs) {
    auto c = _mul(lhs.dat, rhs.dat);
    bool n = _is_zero(c) ? false : (lhs.neg ^ rhs.neg);
    return {n, c};
  }
  friend pair<M, M> divmod(const M& lhs, const M& rhs) {
    auto dm = _divmod_newton(lhs.dat, rhs.dat);
    bool dn = _is_zero(dm.first) ? false : lhs.neg != rhs.neg;
    bool mn = _is_zero(dm.second) ? false : lhs.neg;
    return {M{dn, dm.first}, M{mn, dm.second}};
  }
  friend M operator/(const M& lhs, const M& rhs) {
    return divmod(lhs, rhs).first;
  }
  friend M operator%(const M& lhs, const M& rhs) {
    return divmod(lhs, rhs).second;
  }

  M& operator+=(const M& rhs) { return (*this) = (*this) + rhs; }
  M& operator-=(const M& rhs) { return (*this) = (*this) - rhs; }
  M& operator*=(const M& rhs) { return (*this) = (*this) * rhs; }
  M& operator/=(const M& rhs) { return (*this) = (*this) / rhs; }
  M& operator%=(const M& rhs) { return (*this) = (*this) % rhs; }

  M operator-() const {
    if (is_zero()) return *this;
    return {!neg, dat};
  }
  M operator+() const { return *this; }
  friend M abs(const M& m) { return {false, m.dat}; }
  bool is_zero() const { return _is_zero(dat); }

  friend bool operator==(const M& lhs, const M& rhs) {
    return lhs.neg == rhs.neg && lhs.dat == rhs.dat;
  }
  friend bool operator!=(const M& lhs, const M& rhs) {
    return lhs.neg != rhs.neg || lhs.dat != rhs.dat;
  }
  friend bool operator<(const M& lhs, const M& rhs) {
    if (lhs == rhs) return false;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator<=(const M& lhs, const M& rhs) {
    if (lhs == rhs) return true;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator>(const M& lhs, const M& rhs) {
    if (lhs == rhs) return false;
    return _neq_lt(rhs, lhs);
  }
  friend bool operator>=(const M& lhs, const M& rhs) {
    if (lhs == rhs) return true;
    return _neq_lt(rhs, lhs);
  }

  // a * 10^b (1 <= |a| < 10) の形で渡す
  // 相対誤差：10^{-16} ~ 10^{-19} 程度 (処理系依存)
  pair<long double, int> dfp() const {
    if (is_zero()) return {0, 0};
    int l = max<int>(0, _size() - 3);
    int b = logD * l;
    string prefix{};
    for (int i = _size() - 1; i >= l; i--) {
      prefix += _itos(dat[i], i != _size() - 1);
    }
    b += prefix.size() - 1;
    long double a = 0;
    for (auto& c : prefix) a = a * 10.0 + (c - '0');
    a *= tens.ten_ld(-((int)prefix.size()) + 1);
    a = clamp<long double>(a, 1.0, nextafterl(10.0, 1.0));
    if (neg) a = -a;
    return {a, b};
  }
  string to_string() const {
    if (is_zero()) return "0";
    string res;
    if (neg) res.push_back('-');
    for (int i = _size() - 1; i >= 0; i--) {
      res += _itos(dat[i], i != _size() - 1);
    }
    return res;
  }
  long double to_ld() const {
    auto [a, b] = dfp();
    if (-tens.offset <= b and b <= tens.offset) {
      return a * tens.ten_ld(b);
    }
    return a * powl(10, b);
  }
  long long to_ll() const {
    long long res = _to_ll(dat);
    return neg ? -res : res;
  }
  __int128_t to_i128() const {
    __int128_t res = _to_i128(dat);
    return neg ? -res : res;
  }

  friend istream& operator>>(istream& is, M& m) {
    string s;
    is >> s;
    m = M{s};
    return is;
  }

  friend ostream& operator<<(ostream& os, const M& m) {
    return os << m.to_string();
  }

  // 内部の関数をテスト
  static void _test_private_function(const M&, const M&);

 private:
  // size
  int _size() const { return dat.size(); }
  // a == b
  static bool _eq(const vector<int>& a, const vector<int>& b) { return a == b; }
  // a < b
  static bool _lt(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--) {
      if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
  }
  // a <= b
  static bool _leq(const vector<int>& a, const vector<int>& b) {
    return _eq(a, b) || _lt(a, b);
  }
  // a < b (s.t. a != b)
  static bool _neq_lt(const M& lhs, const M& rhs) {
    assert(lhs != rhs);
    if (lhs.neg != rhs.neg) return lhs.neg;
    bool f = _lt(lhs.dat, rhs.dat);
    if (f) return !lhs.neg;
    return lhs.neg;
  }
  // a == 0
  static bool _is_zero(const vector<int>& a) { return a.empty(); }
  // a == 1
  static bool _is_one(const vector<int>& a) {
    return (int)a.size() == 1 && a[0] == 1;
  }
  // 末尾 0 を削除
  static void _shrink(vector<int>& a) {
    while (a.size() && a.back() == 0) a.pop_back();
  }
  // 末尾 0 を削除
  void _shrink() {
    while (_size() && dat.back() == 0) dat.pop_back();
  }
  // a + b
  static vector<int> _add(const vector<int>& a, const vector<int>& b) {
    vector<int> c(max(a.size(), b.size()) + 1);
    for (int i = 0; i < (int)a.size(); i++) c[i] += a[i];
    for (int i = 0; i < (int)b.size(); i++) c[i] += b[i];
    for (int i = 0; i < (int)c.size() - 1; i++) {
      if (c[i] >= D) c[i] -= D, c[i + 1]++;
    }
    _shrink(c);
    return c;
  }
  // a - b
  static vector<int> _sub(const vector<int>& a, const vector<int>& b) {
    assert(_leq(b, a));
    vector<int> c{a};
    int borrow = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      if (i < (int)b.size()) borrow += b[i];
      c[i] -= borrow;
      borrow = 0;
      if (c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(borrow == 0);
    _shrink(c);
    return c;
  }
  // a * b (fft)
  static vector<int> _mul_fft(const vector<int>& a, const vector<int>& b) {
    if (a.empty() || b.empty()) return {};
    auto m = ArbitraryNTT::multiply_u128(a, b);
    vector<int> c;
    c.reserve(m.size() + 3);
    __uint128_t x = 0;
    for (int i = 0;; i++) {
      if (i >= (int)m.size() && x == 0) break;
      if (i < (int)m.size()) x += m[i];
      c.push_back(x % D);
      x /= D;
    }
    _shrink(c);
    return c;
  }
  // a * b (naive)
  static vector<int> _mul_naive(const vector<int>& a, const vector<int>& b) {
    if (a.empty() || b.empty()) return {};
    vector<long long> prod(a.size() + b.size() - 1 + 1);
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)b.size(); j++) {
        long long p = 1LL * a[i] * b[j];
        prod[i + j] += p;
        if (prod[i + j] >= (4LL * D * D)) {
          prod[i + j] -= 4LL * D * D;
          prod[i + j + 1] += 4LL * D;
        }
      }
    }
    vector<int> c;
    long long x = 0;
    for (int i = 0;; i++) {
      if (i >= (int)prod.size() && x == 0) break;
      if (i < (int)prod.size()) x += prod[i];
      c.push_back(x % D);
      x /= D;
    }
    _shrink(c);
    return c;
  }
  // a * b
  static vector<int> _mul(const vector<int>& a, const vector<int>& b) {
    if (_is_zero(a) || _is_zero(b)) return {};
    if (_is_one(a)) return b;
    if (_is_one(b)) return a;
    if (min<int>(a.size(), b.size()) <= 128) {
      return a.size() < b.size() ? _mul_naive(b, a) : _mul_naive(a, b);
    }
    return _mul_fft(a, b);
  }
  // 0 <= A < 1e18, 1 <= B < 1e9
  static pair<vector<int>, vector<int>> _divmod_li(const vector<int>& a,
                                                   const vector<int>& b) {
    assert(0 <= (int)a.size() && (int)a.size() <= 2);
    assert((int)b.size() == 1);
    long long va = _to_ll(a);
    int vb = b[0];
    return {_integer_to_vec(va / vb), _integer_to_vec(va % vb)};
  }
  // 0 <= A < 1e18, 1 <= B < 1e18
  static pair<vector<int>, vector<int>> _divmod_ll(const vector<int>& a,
                                                   const vector<int>& b) {
    assert(0 <= (int)a.size() && (int)a.size() <= 2);
    assert(1 <= (int)b.size() && (int)b.size() <= 2);
    long long va = _to_ll(a), vb = _to_ll(b);
    return {_integer_to_vec(va / vb), _integer_to_vec(va % vb)};
  }
  // 1 <= B < 1e9
  static pair<vector<int>, vector<int>> _divmod_1e9(const vector<int>& a,
                                                    const vector<int>& b) {
    assert((int)b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if ((int)a.size() <= 2) return _divmod_li(a, b);
    vector<int> quo(a.size());
    long long d = 0;
    int b0 = b[0];
    for (int i = a.size() - 1; i >= 0; i--) {
      d = d * D + a[i];
      assert(d < 1LL * D * b0);
      int q = d / b0, r = d % b0;
      quo[i] = q, d = r;
    }
    _shrink(quo);
    return {quo, d ? vector<int>{int(d)} : vector<int>{}};
  }
  // 0 <= A, 1 <= B
  static pair<vector<int>, vector<int>> _divmod_naive(const vector<int>& a,
                                                      const vector<int>& b) {
    if (_is_zero(b)) {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }
    assert(1 <= (int)b.size());
    if ((int)b.size() == 1) return _divmod_1e9(a, b);
    if (max<int>(a.size(), b.size()) <= 2) return _divmod_ll(a, b);
    if (_lt(a, b)) return {{}, a};
    // B >= 1e9, A >= B
    int norm = D / (b.back() + 1);
    vector<int> x = _mul(a, {norm});
    vector<int> y = _mul(b, {norm});
    int yb = y.back();
    vector<int> quo(x.size() - y.size() + 1);
    vector<int> rem(x.end() - y.size(), x.end());
    for (int i = quo.size() - 1; i >= 0; i--) {
      if (rem.size() < y.size()) {
        // do nothing
      } else if (rem.size() == y.size()) {
        if (_leq(y, rem)) {
          quo[i] = 1, rem = _sub(rem, y);
        }
      } else {
        assert(y.size() + 1 == rem.size());
        long long rb = 1LL * rem[rem.size() - 1] * D + rem[rem.size() - 2];
        int q = rb / yb;
        vector<int> yq = _mul(y, {q});
        // 真の商は q-2 以上 q+1 以下だが自信が無いので念のため while を回す
        while (_lt(rem, yq)) q--, yq = _sub(yq, y);
        rem = _sub(rem, yq);
        while (_leq(y, rem)) q++, rem = _sub(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(begin(rem), x[i - 1]);
    }
    _shrink(quo), _shrink(rem);
    auto [q2, r2] = _divmod_1e9(rem, {norm});
    assert(_is_zero(r2));
    return {quo, q2};
  }

  // 0 <= A, 1 <= B
  static pair<vector<int>, vector<int>> _divmod_dc(const vector<int>& a,
                                                   const vector<int>& b) {
    if (_is_zero(b)) {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }
    if ((int)b.size() <= 64) return _divmod_naive(a, b);
    if ((int)a.size() - (int)b.size() <= 64) return _divmod_naive(a, b);

    int norm = D / (b.back() + 1);
    vector<int> x = _mul(a, {norm});
    vector<int> y = _mul(b, {norm});

    int s = x.size(), t = y.size();
    int yu = (t + 1) / 2, yv = t - yu;
    vector<int> yh{end(y) - yu, end(y)};
    int xv = max<int>(yv, s - (yu * 2 - 1));
    int xu = s - xv;
    vector<int> xh{end(x) - xu, end(x)};
    vector<int> rem{end(x) - xu - yv, end(x)};
    auto [qh, _unused] = _divmod_dc(xh, yh);
    vector<int> yqh = _mul(y, qh);
    while (_lt(rem, yqh)) _sub(qh, {1}), yqh = _sub(yqh, y);
    rem = _sub(rem, yqh);
    while (_leq(y, rem)) _add(qh, {1}), rem = _sub(rem, y);
    vector<int> q, r;
    if (xu + yv == s) {
      swap(q, qh), swap(r, rem);
    } else {
      vector<int> xnxt{begin(x), end(x) - xu - yv};
      copy(begin(rem), end(rem), back_inserter(xnxt));
      tie(q, r) = _divmod_dc(xnxt, y);
      q.resize(s - xu - yv, 0);
      copy(begin(qh), end(qh), back_inserter(q));
    }
    _shrink(q), _shrink(r);
    auto [q2, r2] = _divmod_1e9(r, {norm});
    assert(_is_zero(r2));
    return {q, q2};
  }

  // 1 / a を 絶対誤差 B^{-deg} で求める
  static vector<int> _calc_inv(const vector<int>& a, int deg) {
    assert(!a.empty() && D / 2 <= a.back() and a.back() < D);
    int k = deg, c = a.size();
    while (k > 64) k = (k + 1) / 2;
    vector<int> z(c + k + 1);
    z.back() = 1;
    z = _divmod_naive(z, a).first;
    while (k < deg) {
      vector<int> s = _mul(z, z);
      s.insert(begin(s), 0);
      vector<int> t(2 * k + 1);
      copy(end(a) - min(c, 2 * k + 1), end(a), end(t) - min(c, 2 * k + 1));
      vector<int> u = _mul(s, t);
      u.erase(begin(u), begin(u) + 2 * k + 1);
      vector<int> w(k + 1, 0), w2 = _add(z, z);
      copy(begin(w2), end(w2), back_inserter(w));
      z = _sub(w, u);
      z.erase(begin(z));
      k *= 2;
    }
    z.erase(begin(z), begin(z) + k - deg);
    return z;
  }

  static pair<vector<int>, vector<int>> _divmod_newton(const vector<int>& a,
                                                       const vector<int>& b) {
    if (_is_zero(b)) {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }
    if ((int)b.size() <= 64) return _divmod_naive(a, b);
    if ((int)a.size() - (int)b.size() <= 64) return _divmod_naive(a, b);
    int norm = D / (b.back() + 1);
    vector<int> x = _mul(a, {norm});
    vector<int> y = _mul(b, {norm});
    int s = x.size(), t = y.size();
    int deg = s - t + 2;
    vector<int> z = _calc_inv(y, deg);
    vector<int> q = _mul(x, z);
    q.erase(begin(q), begin(q) + t + deg);
    vector<int> yq = _mul(y, {q});
    while (_lt(x, yq)) q = _sub(q, {1}), yq = _sub(yq, y);
    vector<int> r = _sub(x, yq);
    while (_leq(y, r)) q = _add(q, {1}), r = _sub(r, y);
    _shrink(q), _shrink(r);
    auto [q2, r2] = _divmod_1e9(r, {norm});
    assert(_is_zero(r2));
    return {q, q2};
  }

  // int -> string
  // 先頭かどうかに応じて zero padding するかを決める
  static string _itos(int x, bool zero_padding) {
    assert(0 <= x && x < D);
    string res;
    for (int i = 0; i < logD; i++) {
      res.push_back('0' + x % 10), x /= 10;
    }
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    reverse(begin(res), end(res));
    return res;
  }

  // convert ll to vec
  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>>* = nullptr>
  static vector<int> _integer_to_vec(I x) {
    if constexpr (is_signed_v<I> || is_same_v<I, __int128_t>) {
      assert(x >= 0);
    }
    vector<int> res;
    while (x) res.push_back(x % D), x /= D;
    return res;
  }

  static long long _to_ll(const vector<int>& a) {
    long long res = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) res = res * D + a[i];
    return res;
  }

  static __int128_t _to_i128(const vector<int>& a) {
    __int128_t res = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) res = res * D + a[i];
    return res;
  }

  static void _dump(const vector<int>& a, string s = "") {
    if (!s.empty()) cerr << s << " : ";
    cerr << "{ ";
    for (int i = 0; i < (int)a.size(); i++) cerr << a[i] << ", ";
    cerr << "}" << endl;
  }
};

using bigint = MultiPrecisionInteger;

/**
 * @brief 多倍長整数
 */
