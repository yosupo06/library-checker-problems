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
const int inf = 0x3fffffff;
const ll INF = 0x1fffffffffffffff;

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

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
  os << "P(" << p.first << ", " << p.second << ")";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
  os << "{";
  for (int i = 0; i < vec.size(); i++)
  {
    os << vec[i] << (i + 1 == vec.size() ? "" : ", ");
  }
  os << "}";
  return os;
}
template <typename T, typename U>
ostream &operator<<(ostream &os, const map<T, U> &map_var)
{
  os << "{";
  for (auto itr = map_var.begin(); itr != map_var.end(); itr++)
  {
    os << "(" << itr->first << ", " << itr->second << ")";
    itr++;
    if (itr != map_var.end())
      os << ", ";
    itr--;
  }
  os << "}";
  return os;
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &set_var)
{
  os << "{";
  for (auto itr = set_var.begin(); itr != set_var.end(); itr++)
  {
    os << *itr;
    ++itr;
    if (itr != set_var.end())
      os << ", ";
    itr--;
  }
  os << "}";
  return os;
}
#ifdef LOCAL
#define show(...) _show(0, #__VA_ARGS__, __VA_ARGS__)
#else
#define show(...) true
#endif
template <typename T>
void _show(int i, T name)
{
  cerr << '\n';
}
template <typename T1, typename T2, typename... T3>
void _show(int i, const T1 &a, const T2 &b, const T3 &...c)
{
  for (; a[i] != ',' && a[i] != '\0'; i++)
    cerr << a[i];
  cerr << ":" << b << " ";
  _show(i + 1, a, c...);
}

#include <unistd.h>

namespace fastio
{
  static constexpr uint32_t SZ = 1 << 17;
  char ibuf[SZ];
  char obuf[SZ];
  char out[100];
  // pointer of ibuf, obuf

  uint32_t pil = 0, pir = 0, por = 0;

  struct Pre
  {
    char num[10000][4];
    constexpr Pre() : num()
    {
      for (int i = 0; i < 10000; i++)
      {
        int n = i;
        for (int j = 3; j >= 0; j--)
        {
          num[i][j] = n % 10 | '0';
          n /= 10;
        }
      }
    }
  } constexpr pre;

  inline void load()
  {
    memmove(ibuf, ibuf + pil, pir - pil);
    pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
    pil = 0;
    if (pir < SZ)
      ibuf[pir++] = '\n';
  }

  inline void flush()
  {
    fwrite(obuf, 1, por, stdout);
    por = 0;
  }

  void rd(char &c)
  {
    do
    {
      if (pil + 1 > pir)
        load();
      c = ibuf[pil++];
    } while (isspace(c));
  }

  void rd(string &x)
  {
    x.clear();
    char c;
    do
    {
      if (pil + 1 > pir)
        load();
      c = ibuf[pil++];
    } while (isspace(c));
    do
    {
      x += c;
      if (pil == pir)
        load();
      c = ibuf[pil++];
    } while (!isspace(c));
  }

  template <typename T>
  void rd_real(T &x)
  {
    string s;
    rd(s);
    x = stod(s);
  }

  template <typename T>
  void rd_integer(T &x)
  {
    if (pil + 100 > pir)
      load();
    char c;
    do
      c = ibuf[pil++];
    while (c < '-');
    bool minus = 0;
    if constexpr (is_signed<T>::value || is_same_v<T, i128>)
    {
      if (c == '-')
      {
        minus = 1, c = ibuf[pil++];
      }
    }
    x = 0;
    while ('0' <= c)
    {
      x = x * 10 + (c & 15), c = ibuf[pil++];
    }
    if constexpr (is_signed<T>::value || is_same_v<T, i128>)
    {
      if (minus)
        x = -x;
    }
  }

  void rd(int &x)
  {
    rd_integer(x);
  }
  void rd(ll &x)
  {
    rd_integer(x);
  }
  void rd(i128 &x)
  {
    rd_integer(x);
  }
  void rd(uint &x)
  {
    rd_integer(x);
  }
  void rd(ull &x)
  {
    rd_integer(x);
  }
  void rd(u128 &x)
  {
    rd_integer(x);
  }
  void rd(double &x)
  {
    rd_real(x);
  }
  void rd(long double &x)
  {
    rd_real(x);
  }

  template <class T, class U>
  void rd(pair<T, U> &p)
  {
    return rd(p.first), rd(p.second);
  }
  template <size_t N = 0, typename T>
  void rd_tuple(T &t)
  {
    if constexpr (N < std::tuple_size<T>::value)
    {
      auto &x = std::get<N>(t);
      rd(x);
      rd_tuple<N + 1>(t);
    }
  }
  template <class... T>
  void rd(tuple<T...> &tpl)
  {
    rd_tuple(tpl);
  }

  template <size_t N = 0, typename T>
  void rd(array<T, N> &x)
  {
    for (auto &d : x)
      rd(d);
  }
  template <class T>
  void rd(vector<T> &x)
  {
    for (auto &d : x)
      rd(d);
  }

  void read() {}
  template <class H, class... T>
  void read(H &h, T &...t)
  {
    rd(h), read(t...);
  }

  void wt(const char c)
  {
    if (por == SZ)
      flush();
    obuf[por++] = c;
  }
  void wt(const string s)
  {
    for (char c : s)
      wt(c);
  }
  void wt(const char *s)
  {
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++)
      wt(s[i]);
  }

  template <typename T>
  void wt_integer(T x)
  {
    if (por > SZ - 100)
      flush();
    if (x < 0)
    {
      obuf[por++] = '-', x = -x;
    }
    int outi;
    for (outi = 96; x >= 10000; outi -= 4)
    {
      memcpy(out + outi, pre.num[x % 10000], 4);
      x /= 10000;
    }
    if (x >= 1000)
    {
      memcpy(obuf + por, pre.num[x], 4);
      por += 4;
    }
    else if (x >= 100)
    {
      memcpy(obuf + por, pre.num[x] + 1, 3);
      por += 3;
    }
    else if (x >= 10)
    {
      int q = (x * 103) >> 10;
      obuf[por] = q | '0';
      obuf[por + 1] = (x - q * 10) | '0';
      por += 2;
    }
    else
      obuf[por++] = x | '0';
    memcpy(obuf + por, out + outi + 4, 96 - outi);
    por += 96 - outi;
  }

  template <typename T>
  void wt_real(T x)
  {
    ostringstream oss;
    oss << fixed << setprecision(15) << double(x);
    string s = oss.str();
    wt(s);
  }

  void wt(int x)
  {
    wt_integer(x);
  }
  void wt(ll x)
  {
    wt_integer(x);
  }
  void wt(i128 x)
  {
    wt_integer(x);
  }
  void wt(uint x)
  {
    wt_integer(x);
  }
  void wt(ull x)
  {
    wt_integer(x);
  }
  void wt(u128 x)
  {
    wt_integer(x);
  }
  void wt(double x)
  {
    wt_real(x);
  }
  void wt(long double x)
  {
    wt_real(x);
  }

  template <class T, class U>
  void wt(const pair<T, U> val)
  {
    wt(val.first);
    wt(' ');
    wt(val.second);
  }
  template <size_t N = 0, typename T>
  void wt_tuple(const T t)
  {
    if constexpr (N < std::tuple_size<T>::value)
    {
      if constexpr (N > 0)
      {
        wt(' ');
      }
      const auto x = std::get<N>(t);
      wt(x);
      wt_tuple<N + 1>(t);
    }
  }
  template <class... T>
  void wt(tuple<T...> tpl)
  {
    wt_tuple(tpl);
  }
  template <class T, size_t S>
  void wt(const array<T, S> val)
  {
    auto n = val.size();
    for (size_t i = 0; i < n; i++)
    {
      if (i)
        wt(' ');
      wt(val[i]);
    }
  }
  template <class T>
  void wt(const vector<T> val)
  {
    auto n = val.size();
    for (size_t i = 0; i < n; i++)
    {
      if (i)
        wt(' ');
      wt(val[i]);
    }
  }

  void print()
  {
    wt('\n');
  }
  template <class Head, class... Tail>
  void print(Head &&head, Tail &&...tail)
  {
    wt(head);
    if (sizeof...(Tail))
      wt(' ');
    print(forward<Tail>(tail)...);
  }
  void __attribute__((destructor)) _d()
  {
    flush();
  }
} // namespace fastio

using fastio::flush;
using fastio::print;
using fastio::read;

inline void first(bool i = true)
{
  print(i ? "first" : "second");
}
inline void Alice(bool i = true)
{
  print(i ? "Alice" : "Bob");
}
inline void Takahashi(bool i = true)
{
  print(i ? "Takahashi" : "Aoki");
}
inline void yes(bool i = true)
{
  print(i ? "yes" : "no");
}
inline void Yes(bool i = true)
{
  print(i ? "Yes" : "No");
}
inline void No()
{
  print("No");
}
inline void YES(bool i = true)
{
  print(i ? "YES" : "NO");
}
inline void NO()
{
  print("NO");
}
inline void Yay(bool i = true)
{
  print(i ? "Yay!" : ":(");
}
inline void Possible(bool i = true)
{
  print(i ? "Possible" : "Impossible");
}
inline void POSSIBLE(bool i = true)
{
  print(i ? "POSSIBLE" : "IMPOSSIBLE");
}

/**
 * @brief Fast IO
 */

namespace Random
{
  mt19937_64 randgen(chrono::steady_clock::now().time_since_epoch().count());
  using u64 = unsigned long long;
  u64 get()
  {
    return randgen();
  }
  template <typename T>
  T get(T L)
  { // [0,L]

    return get() % (L + 1);
  }
  template <typename T>
  T get(T L, T R)
  { // [L,R]

    return get(R - L) + L;
  }
  double uniform()
  {
    return double(get(1000000000)) / 1000000000;
  }
  string str(int n)
  {
    string ret;
    rep(i, 0, n) ret += get('a', 'z');
    return ret;
  }
  template <typename Iter>
  void shuffle(Iter first, Iter last)
  {
    if (first == last)
      return;
    int len = 1;
    for (auto it = first + 1; it != last; it++)
    {
      len++;
      int j = get(0, len - 1);
      if (j != len - 1)
        iter_swap(it, first + j);
    }
  }
  template <typename T>
  vector<T> select(int n, T L, T R)
  { // [L,R]

    if (n * 2 >= R - L + 1)
    {
      vector<T> ret(R - L + 1);
      iota(ALL(ret), L);
      shuffle(ALL(ret));
      ret.resize(n);
      return ret;
    }
    else
    {
      unordered_set<T> used;
      vector<T> ret;
      while (SZ(used) < n)
      {
        T x = get(L, R);
        if (!used.count(x))
        {
          used.insert(x);
          ret.push_back(x);
        }
      }
      return ret;
    }
  }

  void relabel(int n, vector<pair<int, int>> &es)
  {
    shuffle(ALL(es));
    vector<int> ord(n);
    iota(ALL(ord), 0);
    shuffle(ALL(ord));
    for (auto &[u, v] : es)
      u = ord[u], v = ord[v];
  }
  template <bool directed, bool simple>
  vector<pair<int, int>> genGraph(int n)
  {
    vector<pair<int, int>> cand, es;
    rep(u, 0, n) rep(v, 0, n)
    {
      if (simple and u == v)
        continue;
      if (!directed and u > v)
        continue;
      cand.push_back({u, v});
    }
    int m = get(SZ(cand));
    vector<int> ord;
    if (simple)
      ord = select(m, 0, SZ(cand) - 1);
    else
    {
      rep(_, 0, m) ord.push_back(get(SZ(cand) - 1));
    }
    for (auto &i : ord)
      es.push_back(cand[i]);
    relabel(n, es);
    return es;
  }
  vector<pair<int, int>> genTree(int n)
  {
    vector<pair<int, int>> es;
    rep(i, 1, n) es.push_back({get(i - 1), i});
    relabel(n, es);
    return es;
  }
}; // namespace Random

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

template <unsigned mod>
void rd(fp<mod> &x)
{
  fastio::rd(x.v);
}
template <unsigned mod>
void wt(fp<mod> x)
{
  fastio::wt(x.v);
}

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