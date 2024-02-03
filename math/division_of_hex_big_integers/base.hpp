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

// 0 は neg=false, bits={} として扱う
struct BigInteger
{
  using M = BigInteger;

  bool neg;
  vector<uint32_t> bits;
  static constexpr int logD = 8;

  BigInteger() : neg(false), bits() {}

  BigInteger(bool n, const vector<uint32_t> &d) : neg(n), bits(d) {}

  BigInteger(uint32_t x) : neg(false)
  {
    bits = _integer_to_vector(x);
  }

  BigInteger(int32_t x) : neg(false)
  {
    if (x < 0)
      neg = true, x = -x;
    bits = _integer_to_vector((uint32_t)x);
  }

  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>> * = nullptr>
  BigInteger(I x) : neg(false)
  {
    if constexpr (is_signed_v<I> || is_same_v<I, __int128_t>)
    {
      if (x < 0)
        neg = true, x = -x;
    }
    bits = _integer_to_vector(x);
  }

  BigInteger(const string &S) : neg(false)
  {
    assert(!S.empty());
    if (S.size() == 1u && S[0] == '0')
      return;
    int l = 0;
    if (S[0] == '-')
      ++l, neg = true;

    for (int ie = S.size(); l < ie; ie -= logD)
    {
      int is = max(l, ie - logD);
      uint32_t x = 0;
      for (int i = is; i < ie; i++)
      {
        x <<= 4;
        if ('0' <= S[i] and S[i] <= '9')
        {
          x |= S[i] - '0';
        }
        else if ('A' <= S[i] and S[i] <= 'F')
        {
          x |= S[i] - 'A' + 10;
        }
        else if ('a' <= S[i] and S[i] <= 'f')
        {
          x |= S[i] - 'a' + 10;
        }
        else
        {
          assert(false);
        }
      }
      bits.push_back(x);
    }
  }

  friend M operator+(const M &lhs, const M &rhs)
  {
    if (lhs.neg == rhs.neg)
      return {lhs.neg, _add(lhs.bits, rhs.bits)};
    if (_leq(lhs.bits, rhs.bits))
    {
      // |l| <= |r|
      auto c = _sub(rhs.bits, lhs.bits);
      bool n = _is_zero(c) ? false : rhs.neg;
      return {n, c};
    }
    auto c = _sub(lhs.bits, rhs.bits);
    bool n = _is_zero(c) ? false : lhs.neg;
    return {n, c};
  }
  friend M operator-(const M &lhs, const M &rhs) { return lhs + (-rhs); }

  friend M operator*(const M &lhs, const M &rhs)
  {
    auto c = _mul(lhs.bits, rhs.bits);
    bool n = _is_zero(c) ? false : (lhs.neg ^ rhs.neg);
    return {n, c};
  }
  friend pair<M, M> divmod(const M &lhs, const M &rhs)
  {
    auto dm = _divmod(lhs.bits, rhs.bits);
    bool dn = _is_zero(dm.first) ? false : lhs.neg != rhs.neg;
    bool mn = _is_zero(dm.second) ? false : lhs.neg;
    return {M{dn, dm.first}, M{mn, dm.second}};
  }
  friend M operator/(const M &lhs, const M &rhs)
  {
    return divmod(lhs, rhs).first;
  }
  friend M operator%(const M &lhs, const M &rhs)
  {
    return divmod(lhs, rhs).second;
  }

  M &operator+=(const M &rhs) { return (*this) = (*this) + rhs; }
  M &operator-=(const M &rhs) { return (*this) = (*this) - rhs; }
  M &operator*=(const M &rhs) { return (*this) = (*this) * rhs; }
  M &operator/=(const M &rhs) { return (*this) = (*this) / rhs; }
  M &operator%=(const M &rhs) { return (*this) = (*this) % rhs; }

  M operator-() const
  {
    if (is_zero())
      return *this;
    return {!neg, bits};
  }
  M operator+() const { return *this; }
  friend M abs(const M &m) { return {false, m.bits}; }
  bool is_zero() const { return _is_zero(bits); }

  friend bool operator==(const M &lhs, const M &rhs)
  {
    return lhs.neg == rhs.neg && lhs.bits == rhs.bits;
  }
  friend bool operator!=(const M &lhs, const M &rhs)
  {
    return lhs.neg != rhs.neg || lhs.bits != rhs.bits;
  }
  friend bool operator<(const M &lhs, const M &rhs)
  {
    if (lhs == rhs)
      return false;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator<=(const M &lhs, const M &rhs)
  {
    if (lhs == rhs)
      return true;
    return _neq_lt(lhs, rhs);
  }
  friend bool operator>(const M &lhs, const M &rhs)
  {
    if (lhs == rhs)
      return false;
    return _neq_lt(rhs, lhs);
  }
  friend bool operator>=(const M &lhs, const M &rhs)
  {
    if (lhs == rhs)
      return true;
    return _neq_lt(rhs, lhs);
  }

  string to_string() const
  {
    if (is_zero())
      return "0";
    string res;
    if (neg)
      res.push_back('-');
    for (int i = _size() - 1; i >= 0; i--)
    {
      res += _itos(bits[i], i != _size() - 1);
    }
    return res;
  }

  friend istream &operator>>(istream &is, M &m)
  {
    string s;
    is >> s;
    m = M{s};
    return is;
  }

  friend ostream &operator<<(ostream &os, const M &m)
  {
    return os << m.to_string();
  }

private:
  // size
  int _size() const { return bits.size(); }
  // a == b
  static bool _eq(const vector<uint32_t> &a, const vector<uint32_t> &b) { return a == b; }
  // a < b
  static bool _lt(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    return _lt(a.cbegin(), a.cend(), b.cbegin(), b.cend());
  }
  // a <= b
  static bool _leq(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    return _eq(a, b) || _lt(a, b);
  }
  // a < b (s.t. a != b)
  static bool _neq_lt(const M &lhs, const M &rhs)
  {
    assert(lhs != rhs);
    if (lhs.neg != rhs.neg)
      return lhs.neg;
    bool f = _lt(lhs.bits, rhs.bits);
    if (f)
      return !lhs.neg;
    return lhs.neg;
  }
  // a == 0
  static bool _is_zero(const vector<uint32_t> &a) { return a.empty(); }
  // a == 1
  static bool _is_one(const vector<uint32_t> &a)
  {
    return (int)a.size() == 1 && a[0] == 1;
  }
  // 末尾 0 を削除
  static void _shrink(vector<uint32_t> &a)
  {
    while (a.size() && a.back() == 0)
      a.pop_back();
  }
  // 末尾 0 を削除
  void _shrink()
  {
    while (_size() && bits.back() == 0)
      bits.pop_back();
  }
  // a + b
  static vector<uint32_t> _add(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    vector<uint32_t> c(max<int>(a.size(), b.size()) + 1);
    _add(
        a.cbegin(), a.cend(),
        b.cbegin(), b.cend(),
        c.begin(), c.end());
    _shrink(c);
    return c;
  }
  // a - b
  static vector<uint32_t> _sub(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    assert(_leq(b, a));
    vector<uint32_t> c{a};
    _sub(
        c.begin(), c.end(),
        b.cbegin(), b.cend());
    _shrink(c);
    return c;
  }

  // a * b
  static vector<uint32_t> _mul(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    if (_is_zero(a) || _is_zero(b))
      return {};
    if (_is_one(a))
      return b;
    if (_is_one(b))
      return a;

    vector<uint32_t> c(a.size() + b.size());
    _mul(
        a.cbegin(), a.cend(),
        b.cbegin(), b.cend(),
        c.begin(), c.end());
    _shrink(c);
    return c;
  }

  // a / b
  static pair<vector<uint32_t>, vector<uint32_t>> _divmod(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    if (_is_zero(b))
    {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }

    if (a.size() < b.size())
    {
      return {{}, a};
    }

    vector<uint32_t> q(a.size() - b.size() + 1);
    vector<uint32_t> r(b.size());

    _divmod(
        a.cbegin(), a.cend(),
        b.cbegin(), b.cend(),
        q.begin(), q.end(),
        r.begin(), r.end());
    _shrink(q);
    _shrink(r);
    return {q, r};
  }

  using iter = typename vector<uint32_t>::iterator;
  using citer = typename vector<uint32_t>::const_iterator;

  // a + b
  static void _add(
      citer a, citer a_end,
      citer b, citer b_end,
      iter c, iter c_end)
  {
    if (a_end - a < b_end - b)
    {
      swap(a, b);
      swap(a_end, b_end);
    }
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t csize = c_end - c;
    assert(asize <= csize);

    uint32_t carry = 0;
    for (size_t i = 0; i < bsize; i++)
    {
      uint64_t v = (uint64_t)a[i] + b[i] + carry;
      c[i] = (uint32_t)v;
      carry = v >> 32;
    }
    for (size_t i = bsize; i < asize; i++)
    {
      uint64_t v = (uint64_t)a[i] + carry;
      c[i] = (uint32_t)v;
      carry = v >> 32;
    }
    if (carry != 0)
    {
      assert(c + asize < c_end);
      c[asize] = carry;
    }
  }

  // a += b
  static void _add(
      iter a, iter a_end,
      citer b, citer b_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;

    uint32_t carry = 0;
    for (size_t i = 0; i < bsize; i++)
    {
      uint64_t v = (uint64_t)a[i] + b[i] + carry;
      a[i] = (uint32_t)v;
      carry = v >> 32;
    }
    for (size_t i = bsize; carry != 0 && i < asize; i++)
    {
      uint64_t v = (uint64_t)a[i] + carry;
      a[i] = (uint32_t)v;
      carry = v >> 32;
    }
  }
  // a -= b
  static void _sub(
      iter a, iter a_end,
      citer b, citer b_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;

    int32_t carry = 0;
    for (size_t i = 0; i < bsize; i++)
    {
      int64_t v = (int64_t)a[i] - b[i] + carry;
      a[i] = v;
      carry = v >> 32;
    }
    for (size_t i = bsize; carry != 0 && i < asize; i++)
    {
      int64_t v = (int64_t)a[i] + carry;
      a[i] = v;
      carry = v >> 32;
    }
    assert(carry == 0);
  }

  // a * b
  static void _mul(
      citer a, citer a_end,
      citer b, citer b_end,
      iter c, iter c_end)
  {
    if (a_end - a < b_end - b)
    {
      swap(a, b);
      swap(a_end, b_end);
    }
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t csize = c_end - c;
    assert(csize == asize + bsize);

    if (bsize <= 128)
    {
      _mul_naive(
          a, a_end,
          b, b_end,
          c, c_end);
      return;
    }
    // a * b (karatsuba)
    // https://ja.wikipedia.org/wiki/%E3%82%AB%E3%83%A9%E3%83%84%E3%83%90%E6%B3%95
    // |  A_hi  |  A_lo  |
    // |  B_hi  |  B_lo  |

    // z0 := A_lo * B_lo
    // z2 := A_hi * B_hi
    // z1 := A_hi * B_lo + A_lo * B_hi

    // z1 = (A_hi+A_lo) * (B_hi+B_lo) - z0 - z2

    // A * B = (z2<<(2*shift)) + (z1<<shift) + z0

    const size_t n = (asize) >> 1;
    if (bsize <= n)
    {
      // |  A_hi  |  A_lo  |
      // |   0    |   B    |

      // A_lo * B
      _mul(
          a, a + n,
          b, b_end,
          c, c + n + bsize);

      vector<uint32_t> carry(c + n, c + n + bsize);
      fill(c + n, c + n + bsize, 0);

      // A_hi * B
      _mul(
          a + n, a_end,
          b, b_end,
          c + n, c_end);

      _add(c + n, c_end,
           carry.cbegin(), carry.cend());
    }
    else
    {
      // A_lo * B_lo
      _mul(
          a, a + n,
          b, b + n,
          c, c + n + n);

      // A_hi * B_hi
      _mul(
          a + n, a_end,
          b + n, b_end,
          c + n + n, c_end);

      vector<uint32_t> a1(asize - n + 1);
      vector<uint32_t> b1(n + 1);
      vector<uint32_t> z1(asize + 2);
      _add(
          a, a + n,
          a + n, a_end,
          a1.begin(), a1.end());
      _add(
          b, b + n,
          b + n, b_end,
          b1.begin(), b1.end());
      _mul(
          a1.cbegin(), a1.cend(),
          b1.cbegin(), b1.cend(),
          z1.begin(), z1.end());

      _sub(
          z1.begin(), z1.end(),
          c, c + n + n);
      _sub(
          z1.begin(), z1.end(),
          c + n + n, c_end);

      _shrink(z1);
      _add(c + n, c_end,
           z1.begin(), z1.end());
    }
  }

  // a * b (naive)
  static void _mul_naive(
      citer a, citer a_end,
      citer b, citer b_end,
      iter c, iter c_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t csize = c_end - c;
    if (asize == 0 || bsize == 0)
      return;
    assert(csize == asize + bsize);

    for (size_t i = 0; i < asize; i++)
    {
      uint32_t carry = 0;
      for (size_t j = 0; j < bsize; j++)
      {
        uint64_t p = 1LL * a[i] * b[j] + carry + c[i + j];
        c[i + j] = p;
        carry = p >> 32;
      }
      c[i + bsize] = carry;
    }
  }

  static const int _div_naive_th = 64;

  // a / b
  static void _divmod(
      citer a, citer a_end,
      citer b, citer b_end,
      iter quo, iter quo_end,
      iter rem, iter rem_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t qsize = quo_end - quo;
    const size_t rsize = rem_end - rem;

    assert(bsize > 0);
    assert(qsize == asize - bsize + 1);
    assert(rsize == bsize);

    if (min(asize - bsize, bsize) <= _div_naive_th)
    {
      _divmod_naive(
          a, a_end,
          b, b_end,
          quo, quo_end,
          rem, rem_end);
      return;
    }

    // Burnikel-Ziegler の再帰除算アルゴリズム
    // Fast Recursive Division
    // Burnikel, C., Ziegler, J.: Fast recursive division. Research Report MPI-I-98-1-022, MPI Saarbrücken, 1998
    // https://citeseerx.ist.psu.edu/pdf/c9d46de024099fb3fbd44030ddfba1561738939e

    size_t n;
    {
      size_t m = (bsize + _div_naive_th - 1) / _div_naive_th;
      if (m > 1)
        m = 1 << (32 - __builtin_clz(m - 1));

      size_t j = (bsize + m - 1) / m;
      n = j * m;
    }

    const int sigmaDigit = n - bsize;
    const int sigmaShift = __builtin_clz(*(b_end - 1));

    vector<uint32_t> x(asize + sigmaDigit + (__builtin_clz(*(a_end - 1)) <= sigmaShift ? 1 : 0));
    vector<uint32_t> y(n);
    vector<uint32_t> r(n + 1);
    vector<uint32_t> z(2 * n);

    copy(a, a_end, x.begin() + sigmaDigit);
    copy(b, b_end, y.begin() + sigmaDigit);

    _left_shift(x.begin() + sigmaDigit, x.end(), sigmaShift);
    _left_shift(y.begin() + sigmaDigit, y.end(), sigmaShift);

    size_t t = max<size_t>(2, (x.size() + n - 1) / n);
    copy(x.cbegin() + (t - 2) * n, x.cend(), z.begin());

    const size_t quo_upper_len = quo_end - (quo + (t - 2) * n);
    if (quo_upper_len < n)
    {
      vector<uint32_t> qq(n);
      _divmod_d2n1n(
          z.begin(), z.end(),
          y.begin(), y.end(),
          qq.begin(), qq.end(),
          r.begin(), r.end());
      copy(qq.cbegin(), qq.cbegin() + quo_upper_len, quo + (t - 2) * n);
    }
    else
    {
      _divmod_d2n1n(
          z.begin(), z.end(),
          y.begin(), y.end(),
          quo + (t - 2) * n, quo + (t - 1) * n,
          r.begin(), r.end());
    }

    for (int i = t - 3; i >= 0; --i)
    {
      copy(x.begin() + i * n, x.begin() + (i + 1) * n, z.begin());
      copy(r.begin(), r.begin() + n, z.begin() + n);
      fill(r.begin(), r.end(), 0);

      _divmod_d2n1n(
          z.begin(), z.end(),
          y.begin(), y.end(),
          quo + i * n, quo + (i + 1) * n,
          r.begin(), r.end());
    }

    _shrink(r);
    copy(r.cbegin() + sigmaDigit, r.cbegin() + sigmaDigit + rsize, rem);
    _right_shift(rem, rem_end, sigmaShift);
  }

  // a(2n bits) / b(n bits)
  static void _divmod_d2n1n(
      citer a, citer a_end,
      citer b, citer b_end,
      iter quo, iter quo_end,
      iter rem, iter rem_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t qsize = quo_end - quo;
    const size_t rsize = rem_end - rem;
    const size_t n = bsize;

    assert(asize == 2 * n);
    assert(qsize == n);
    assert(rsize == n + 1);

    if (n % 2 != 0 || n <= _div_naive_th)
    {
      _divmod_naive(
          a, a_end,
          b, b_end,
          quo, quo_end,
          rem, rem_end);
      return;
    }
    const size_t half = n >> 1;
    vector<uint32_t> r1(n + half + 1);
    copy(a, a + half, r1.begin());

    _divmod_d3n2n(
        a + half, a_end,
        b, b_end,
        quo + half, quo_end,
        r1.begin() + half, r1.end());
    _divmod_d3n2n(
        r1.cbegin(), r1.cend() - 1,
        b, b_end,
        quo, quo + half,
        rem, rem_end);
  }

  // a(3n bits) / b(2n bits)
  static void _divmod_d3n2n(
      citer a, citer a_end,
      citer b, citer b_end,
      iter quo, iter quo_end,
      iter rem, iter rem_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    const size_t qsize = quo_end - quo;
    const size_t rsize = rem_end - rem;
    const size_t n = bsize >> 1;

    assert(asize == 3 * n);
    assert(bsize == 2 * n);
    assert(qsize == n);
    assert(rsize == 2 * n + 1);
    assert(_lt(a + n + n, a_end, b + n, b_end));

    _divmod_d2n1n(
        a + n, a_end,
        b + n, b_end,
        quo, quo_end,
        rem + n, rem_end);

    vector<uint32_t> d(2 * n);
    _mul(
        quo, quo_end,
        b, b + n,
        d.begin(), d.end());
    copy(a, a + n, rem);

    while (_lt(rem, rem_end, d.cbegin(), d.cend()))
    {
      _add(rem, rem_end, b, b_end);
      vector<uint32_t> one{1};
      _sub(quo, quo_end, one.cbegin(), one.cend());
    }
    _sub(rem, rem_end, d.cbegin(), d.cend());
  }

  // a / b (naive)
  static void _divmod_naive(
      citer a, citer a_end,
      citer b, citer b_end,
      iter quo, iter quo_end,
      iter rem, iter rem_end)
  {
    const size_t asize = a_end - a;
    const size_t bsize = b_end - b;
    if (bsize == 0)
    {
      cerr << "Divide by Zero Exception" << endl;
      exit(1);
    }

    if (bsize == 1)
    {
      uint64_t carry = 0;
      for (size_t i = asize - 1; 0 <= (int)i; --i)
      {
        uint64_t v = (carry << 32) | a[i];
        quo[i] = v / (*b);
        carry = v - quo[i] * (*b);
      }
      *rem = (uint32_t)carry;
      return;
    }
    if (max(asize, bsize) <= 2)
    {
      uint64_t a64 = _iter_to_integer<uint64_t>(a, a_end), b64 = _iter_to_integer<uint64_t>(b, b_end);
      _integer_to_iter(a64 / b64, quo, quo_end);
      _integer_to_iter(a64 % b64, rem, rem_end);
      return;
    }
    if (_lt(a, a_end, b, b_end))
    {
      if (asize > bsize)
        a_end = a + bsize;
      copy(a, a_end, rem);
      return;
    }
    // B > 0xFFFFFFFF, A >= B

    // 割る数のビットを大きくする
    const int shift = __builtin_clz(*(b_end - 1));
    vector<uint32_t> x(asize + (__builtin_clz(*(a_end - 1)) < shift ? 1 : 0));
    copy(a, a_end, x.begin());
    vector<uint32_t> y(b, b_end);

    _left_shift(x.begin(), x.end(), shift);
    _left_shift(y.begin(), y.end(), shift);

    uint32_t yb = y.back();
    vector<uint32_t> qv(x.size() - y.size() + 1);
    vector<uint32_t> rv(x.end() - y.size(), x.end());
    for (int i = qv.size() - 1; i >= 0; i--)
    {
      if (rv.size() < y.size())
      {
        // do nothing
      }
      else if (rv.size() == y.size())
      {
        if (_leq(y, rv))
        {
          qv[i] = 1, rv = _sub(rv, y);
        }
      }
      else
      {
        assert(y.size() + 1 == rv.size());
        uint64_t rb = rv[rv.size() - 1];
        rb <<= 32;
        rb |= rv[rv.size() - 2];
        uint32_t q = rb / yb;
        vector<uint32_t> yq = _mul(y, {q});
        // 真の商は q-2 以上 q+1 以下だが自信が無いので念のため while を回す
        while (_lt(rv, yq))
          q--, yq = _sub(yq, y);
        rv = _sub(rv, yq);
        while (_leq(y, rv))
          q++, rv = _sub(rv, y);
        qv[i] = q;
      }
      if (i)
        rv.insert(begin(rv), x[i - 1]);
      _shrink(rv);
    }

    _shrink(qv);
    _right_shift(rv.begin(), rv.end(), shift);
    _shrink(rv);

    copy(qv.cbegin(), qv.cend(), quo);
    copy(rv.cbegin(), rv.cend(), rem);
  }

  // int -> string
  // 先頭かどうかに応じて zero padding するかを決める
  static string _itos(uint32_t x, bool zero_padding)
  {
    string res;
    for (int i = 0; i < logD; i++)
    {
      uint32_t d = x % 16;
      if (d < 10)
        res.push_back('0' + d);
      else if (d < 16)
        res.push_back('A' + d - 10);
      else
        assert(false);
      x /= 16;
    }
    if (!zero_padding)
    {
      while (res.size() && res.back() == '0')
        res.pop_back();
      assert(!res.empty());
    }
    reverse(begin(res), end(res));
    return res;
  }

  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>> * = nullptr>
  static I _iter_to_integer(citer it, const citer end)
  {
    I res = 0;
    int shift = 0;
    while (it != end)
    {
      res |= (I)*it << shift;
      shift += 32;
      ++it;
    }
    return res;
  }

  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>> * = nullptr>
  static void _integer_to_iter(I x, iter it, const iter end)
  {
    if constexpr (is_signed_v<I> || is_same_v<I, __int128_t>)
    {
      assert(x >= 0);
    }
    while (x)
    {
      assert(it < end);
      *it = (uint32_t)x;
      ++it;
      x >>= 32;
    }
  }

  static vector<uint32_t> _integer_to_vector(uint32_t x)
  {
    return vector<uint32_t>{x};
  }

  template <typename I, enable_if_t<is_integral_v<I> ||
                                    is_same_v<I, __int128_t>> * = nullptr>
  static vector<uint32_t> _integer_to_vector(I x)
  {
    if constexpr (is_signed_v<I> || is_same_v<I, __int128_t>)
    {
      assert(x >= 0);
    }
    vector<uint32_t> rt;
    while (x)
    {
      rt.push_back((uint32_t)x);
      x >>= 32;
    }
    return rt;
  }

  // a << shift
  static void _left_shift(const iter a, const iter a_end, int shift)
  {
    assert(shift < 32);
    if (shift == 0)
      return;
    const int back = 32 - shift;
    uint32_t carry = 0;
    for (iter it = a; it < a_end; ++it)
    {
      uint32_t v = (*it << shift) | carry;
      carry = *it >> back;
      *it = v;
    }
    assert(carry == 0);
  }
  // a >> shift
  static void _right_shift(const iter a, const iter a_end, int shift)
  {
    assert(shift < 32);
    if (shift == 0)
      return;
    const int back = 32 - shift;
    uint32_t carry = 0;
    for (iter it = a_end - 1; a <= it; --it)
    {
      uint32_t v = (*it >> shift) | carry;
      carry = *it << back;
      *it = v;
    }
    assert(carry == 0);
  }

  // a < b
  static bool _lt(
      citer a, citer a_end,
      citer b, citer b_end)
  {
    size_t asize = a_end - a;
    size_t bsize = b_end - b;

    if (asize != bsize)
    {
      if (asize < bsize)
      {
        auto non_zero = std::find_if(b + asize, b_end, [](uint32_t x)
                                     { return x != 0; });
        if (non_zero != b_end)
          return true;

        b_end = b + asize;
        bsize = asize;
      }
      else
      {
        auto non_zero = std::find_if(a + bsize, a_end, [](uint32_t x)
                                     { return x != 0; });
        if (non_zero != a_end)
          return false;
        a_end = a + bsize;
        asize = bsize;
      }
    }
    for (int i = asize - 1; i >= 0; i--)
    {
      if (a[i] != b[i])
        return a[i] < b[i];
    }
    return false;
  }

  static void _dump(const vector<uint32_t> &a, string s = "")
  {
    if (!s.empty())
      cerr << s << " : ";
    cerr << "{ ";
    for (int i = 0; i < (int)a.size(); i++)
      cerr << a[i] << ", ";
    cerr << "}" << endl;
  }
};

using bigint = BigInteger;

/**
 * @brief 多倍長整数
 */
