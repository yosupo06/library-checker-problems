#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <cstring>
#include <cassert>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define rrep(i, a, b) for (int i = (int)(b)-1; i >= (int)(a); i--)
#define ALL(v) (v).begin(), (v).end()
#define UNIQUE(v) sort(ALL(v)), (v).erase(unique(ALL(v)), (v).end())
#define SZ(v) (int)v.size()
#define MIN(v) *min_element(ALL(v))
#define MAX(v) *max_element(ALL(v))
#define LB(v, x) int(lower_bound(ALL(v), (x)) - (v).begin())
#define UB(v, x) int(upper_bound(ALL(v), (x)) - (v).begin())

using uint = unsigned int;
using ll = long long int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T>
inline bool chmax(T &a, T b)
{
  if (a < b)
  {
    a = b;
    return 1;
  }
  return 0;
}
template <typename T>
inline bool chmin(T &a, T b)
{
  if (a > b)
  {
    a = b;
    return 1;
  }
  return 0;
}
template <typename T, typename U>
T ceil(T x, U y)
{
  assert(y != 0);
  if (y < 0)
    x = -x, y = -y;
  return (x > 0 ? (x + y - 1) / y : x / y);
}
template <typename T, typename U>
T floor(T x, U y)
{
  assert(y != 0);
  if (y < 0)
    x = -x, y = -y;
  return (x > 0 ? x / y : (x - y + 1) / y);
}
template <typename T>
int popcnt(T x)
{
  return __builtin_popcountll(x);
}
template <typename T>
int topbit(T x)
{
  return (x == 0 ? -1 : 63 - __builtin_clzll(x));
}
template <typename T>
int lowbit(T x)
{
  return (x == 0 ? -1 : __builtin_ctzll(x));
}

template <unsigned mod = 1000000007>
struct fp
{
  unsigned v;
  static constexpr int get_mod()
  {
    return mod;
  }
  constexpr unsigned inv() const
  {
    assert(v != 0);
    int x = v, y = mod, p = 1, q = 0, t = 0, tmp = 0;
    while (y > 0)
    {
      t = x / y;
      x -= t * y, p -= t * q;
      tmp = x, x = y, y = tmp;
      tmp = p, p = q, q = tmp;
    }
    if (p < 0)
      p += mod;
    return p;
  }
  constexpr fp(ll x = 0) : v(x >= 0 ? x % mod : (mod - (-x) % mod) % mod) {}
  fp operator-() const
  {
    return fp() - *this;
  }
  fp pow(ull t)
  {
    fp res = 1, b = *this;
    while (t)
    {
      if (t & 1)
        res *= b;
      b *= b;
      t >>= 1;
    }
    return res;
  }
  fp &operator+=(const fp &x)
  {
    if ((v += x.v) >= mod)
      v -= mod;
    return *this;
  }
  fp &operator-=(const fp &x)
  {
    if ((v += mod - x.v) >= mod)
      v -= mod;
    return *this;
  }
  fp &operator*=(const fp &x)
  {
    v = ull(v) * x.v % mod;
    return *this;
  }
  fp &operator/=(const fp &x)
  {
    v = ull(v) * x.inv() % mod;
    return *this;
  }
  fp operator+(const fp &x) const
  {
    return fp(*this) += x;
  }
  fp operator-(const fp &x) const
  {
    return fp(*this) -= x;
  }
  fp operator*(const fp &x) const
  {
    return fp(*this) *= x;
  }
  fp operator/(const fp &x) const
  {
    return fp(*this) /= x;
  }
  bool operator==(const fp &x) const
  {
    return v == x.v;
  }
  bool operator!=(const fp &x) const
  {
    return v != x.v;
  }
  friend istream &operator>>(istream &is, fp &x)
  {
    return is >> x.v;
  }
  friend ostream &operator<<(ostream &os, const fp &x)
  {
    return os << x.v;
  }
};

template <class T>
struct Matrix
{
  int h, w;
  vector<vector<T>> val;
  T det;
  Matrix() {}
  Matrix(int n) : h(n), w(n), val(vector<vector<T>>(n, vector<T>(n))) {}
  Matrix(int n, int m)
      : h(n), w(m), val(vector<vector<T>>(n, vector<T>(m))) {}
  vector<T> &operator[](const int i)
  {
    return val[i];
  }
  Matrix &operator+=(const Matrix &m)
  {
    assert(h == m.h and w == m.w);
    rep(i, 0, h) rep(j, 0, w) val[i][j] += m.val[i][j];
    return *this;
  }
  Matrix &operator-=(const Matrix &m)
  {
    assert(h == m.h and w == m.w);
    rep(i, 0, h) rep(j, 0, w) val[i][j] -= m.val[i][j];
    return *this;
  }
  Matrix &operator*=(const Matrix &m)
  {
    assert(w == m.h);
    Matrix<T> res(h, m.w);
    rep(i, 0, h) rep(j, 0, m.w) rep(k, 0, w) res.val[i][j] +=
        val[i][k] * m.val[k][j];
    *this = res;
    return *this;
  }
  Matrix operator+(const Matrix &m) const
  {
    return Matrix(*this) += m;
  }
  Matrix operator-(const Matrix &m) const
  {
    return Matrix(*this) -= m;
  }
  Matrix operator*(const Matrix &m) const
  {
    return Matrix(*this) *= m;
  }
  Matrix pow(ll k)
  {
    Matrix<T> res(h, h), c = *this;
    rep(i, 0, h) res.val[i][i] = 1;
    while (k)
    {
      if (k & 1)
        res *= c;
      c *= c;
      k >>= 1;
    }
    return res;
  }
  vector<int> gauss(int c = -1)
  {
    det = 1;
    if (val.empty())
      return {};
    if (c == -1)
      c = w;
    int cur = 0;
    vector<int> res;
    rep(i, 0, c)
    {
      if (cur == h)
        break;
      rep(j, cur, h) if (val[j][i] != 0)
      {
        swap(val[cur], val[j]);
        if (cur != j)
          det *= -1;
        break;
      }
      det *= val[cur][i];
      if (val[cur][i] == 0)
        continue;
      rep(j, 0, h) if (j != cur)
      {
        T z = val[j][i] / val[cur][i];
        rep(k, i, w) val[j][k] -= val[cur][k] * z;
      }
      res.push_back(i);
      cur++;
    }
    return res;
  }
  Matrix inv()
  {
    assert(h == w);
    Matrix base(h, h * 2), res(h, h);
    rep(i, 0, h) rep(j, 0, h) base[i][j] = val[i][j];
    rep(i, 0, h) base[i][h + i] = 1;
    base.gauss(h);
    det = base.det;
    rep(i, 0, h) rep(j, 0, h) res[i][j] = base[i][h + j] / base[i][i];
    return res;
  }
  bool operator==(const Matrix &m)
  {
    assert(h == m.h and w == m.w);
    rep(i, 0, h) rep(j, 0, w) if (val[i][j] != m.val[i][j]) return false;
    return true;
  }
  bool operator!=(const Matrix &m)
  {
    assert(h == m.h and w == m.w);
    rep(i, 0, h) rep(j, 0, w) if (val[i][j] == m.val[i][j]) return false;
    return true;
  }
  friend istream &operator>>(istream &is, Matrix &m)
  {
    rep(i, 0, m.h) rep(j, 0, m.w) is >> m[i][j];
    return is;
  }
  friend ostream &operator<<(ostream &os, Matrix &m)
  {
    rep(i, 0, m.h)
    {
      rep(j, 0, m.w) os << m[i][j]
                        << (j == m.w - 1 and i != m.h - 1 ? '\n' : ' ');
    }
    return os;
  }
};

template <typename T>
T Pfaffian(Matrix<T> &a)
{
  int n = a.h;
  assert(n == a.w and n % 2 == 0);
  T ret = 1;
  for (int i = 1; i < n; i += 2)
  {
    rep(j, i, n) if (a[j][i - 1] != 0)
    {
      swap(a[j], a[i]);
      for (auto &v : a.val)
        swap(v[j], v[i]);
      if (i != j)
        ret = -ret;
      break;
    }
    if (a[i][i - 1] == 0)
      return 0;
    ret *= -a[i][i - 1];
    T inv = T(1) / a[i][i - 1];
    rep(j, i + 1, n)
    {
      T z = a[j][i - 1] * inv;
      rep(k, 0, n) a[j][k] -= z * a[i][k];
    }
    inv = T(1) / a[i - 1][i];
    rep(j, i + 1, n)
    {
      T z = a[i - 1][j] * inv;
      rep(k, 0, n) a[k][j] -= z * a[k][i];
    }
  }
  return ret;
}

using Fp = fp<998244353>;

int main()
{
  int n;
  scanf("%d", &n);
  Matrix<Fp> mat(n * 2, n * 2);
  rep(i, 0, n * 2) rep(j, 0, n * 2)
  {
    scanf("%d", &mat[i][j].v);
  }
  auto ret = Pfaffian(mat);
  printf("%d\n", ret.v);
  return 0;
}