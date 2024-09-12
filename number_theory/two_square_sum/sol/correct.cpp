#include <cstdlib>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include <cassert>
#include <cstdint>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define FOR_subset(t, s) for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a: A) sm += a;
  return sm;
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

u64 RNG_64() {
  // library checker なので fixed seed
  static uint64_t x_ = 10402452321532715448ULL;
  x_ ^= x_ << 7;
  return x_ ^= x_ >> 9;
}

u64 RNG(u64 lim) { return RNG_64() % lim; }

ll RNG(ll l, ll r) { return l + RNG_64() % (r - l); }

// odd mod.
// x の代わりに rx を持つ
template <int id, typename U1, typename U2>
struct Mongomery_modint {
  using mint = Mongomery_modint;
  inline static U1 m, r, n2;
  static constexpr int W = numeric_limits<U1>::digits;

  static void set_mod(U1 mod) {
    assert(mod & 1 && mod <= U1(1) << (W - 2));
    m = mod, n2 = -U2(m) % m, r = m;
    FOR(5) r *= 2 - m * r;
    r = -r;
    assert(r * m == U1(-1));
  }
  static U1 reduce(U2 b) { return (b + U2(U1(b) * r) * m) >> W; }

  U1 x;
  Mongomery_modint() : x(0) {}
  Mongomery_modint(U1 x) : x(reduce(U2(x) * n2)){};
  U1 val() const {
    U1 y = reduce(x);
    return y >= m ? y - m : y;
  }
  mint &operator+=(mint y) {
    x = ((x += y.x) >= m ? x - m : x);
    return *this;
  }
  mint &operator-=(mint y) {
    x -= (x >= y.x ? y.x : y.x - m);
    return *this;
  }
  mint &operator*=(mint y) {
    x = reduce(U2(x) * y.x);
    return *this;
  }
  mint operator+(mint y) const { return mint(*this) += y; }
  mint operator-(mint y) const { return mint(*this) -= y; }
  mint operator*(mint y) const { return mint(*this) *= y; }
  bool operator==(mint y) const { return (x >= m ? x - m : x) == (y.x >= m ? y.x - m : y.x); }
  bool operator!=(mint y) const { return not operator==(y); }
  mint pow(ll n) const {
    assert(n >= 0);
    mint y = 1, z = *this;
    for (; n; n >>= 1, z *= z)
      if (n & 1) y *= z;
    return y;
  }
};

template <int id>
using Mongomery_modint_32 = Mongomery_modint<id, u32, u64>;
template <int id>
using Mongomery_modint_64 = Mongomery_modint<id, u64, u128>;

bool primetest(const u64 x) {
  assert(x < u64(1) << 62);
  if (x == 2 or x == 3 or x == 5 or x == 7) return true;
  if (x % 2 == 0 or x % 3 == 0 or x % 5 == 0 or x % 7 == 0) return false;
  if (x < 121) return x > 1;
  const u64 d = (x - 1) >> lowbit(x - 1);

  using mint = Mongomery_modint_64<202311020>;

  mint::set_mod(x);
  const mint one(u64(1)), minus_one(x - 1);
  auto ok = [&](u64 a) -> bool {
    auto y = mint(a).pow(d);
    u64 t = d;
    while (y != one && y != minus_one && t != x - 1) y *= y, t <<= 1;
    if (y != minus_one && t % 2 == 0) return false;
    return true;
  };
  if (x < (u64(1) << 32)) {
    for (u64 a: {2, 7, 61})
      if (!ok(a)) return false;
  } else {
    for (u64 a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if (!ok(a)) return false;
    }
  }
  return true;
}

template <typename mint>
ll rho(ll n, ll c) {
  assert(n > 1);
  const mint cc(c);
  auto f = [&](mint x) { return x * x + cc; };
  mint x = 1, y = 2, z = 1, q = 1;
  ll g = 1;
  const ll m = 1LL << (__lg(n) / 5);
  for (ll r = 1; g == 1; r <<= 1) {
    x = y;
    FOR(r) y = f(y);
    for (ll k = 0; k < r && g == 1; k += m) {
      z = y;
      FOR(min(m, r - k)) y = f(y), q *= x - y;
      g = gcd(q.val(), n);
    }
  }
  if (g == n) do {
      z = f(z);
      g = gcd((x - z).val(), n);
    } while (g == 1);
  return g;
}

ll find_prime_factor(ll n) {
  assert(n > 1);
  if (primetest(n)) return n;
  FOR(100) {
    ll m = 0;
    if (n < (1 << 30)) {
      using mint = Mongomery_modint_32<20231025>;
      mint::set_mod(n);
      m = rho<mint>(n, RNG(0, n));
    } else {
      using mint = Mongomery_modint_64<20231025>;
      mint::set_mod(n);
      m = rho<mint>(n, RNG(0, n));
    }
    if (primetest(m)) return m;
    n = m;
  }
  assert(0);
  return -1;
}

// ソートしてくれる
vc<pair<ll, int>> factor(ll n) {
  assert(n >= 1);
  vc<pair<ll, int>> pf;
  FOR(p, 2, 100) {
    if (p * p > n) break;
    if (n % p == 0) {
      ll e = 0;
      do { n /= p, e += 1; } while (n % p == 0);
      pf.eb(p, e);
    }
  }
  while (n > 1) {
    ll p = find_prime_factor(n);
    ll e = 0;
    do { n /= p, e += 1; } while (n % p == 0);
    pf.eb(p, e);
  }
  sort(all(pf));
  return pf;
}

vc<pair<ll, int>> factor_by_lpf(ll n, vc<int> &lpf) {
  vc<pair<ll, int>> res;
  while (n > 1) {
    int p = lpf[n];
    int e = 0;
    while (n % p == 0) {
      n /= p;
      ++e;
    }
    res.eb(p, e);
  }
  return res;
}

// https://github.com/atcoder/ac-library/blob/master/atcoder/internal_math.hpp
struct Barrett {
  u32 m;
  u64 im;
  explicit Barrett(u32 m = 1) : m(m), im(u64(-1) / m + 1) {}
  u32 umod() const { return m; }
  u32 modulo(u64 z) {
    if (m == 1) return 0;
    u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    u64 y = x * m;
    return (z - y + (z < y ? m : 0));
  }
  u64 floor(u64 z) {
    if (m == 1) return z;
    u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    u64 y = x * m;
    return (z < y ? x - 1 : x);
  }
  pair<u64, u32> divmod(u64 z) {
    if (m == 1) return {z, 0};
    u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    u64 y = x * m;
    if (z < y) return {x - 1, z - y + m};
    return {x, z - y};
  }
  u32 mul(u32 a, u32 b) { return modulo(u64(a) * b); }
};

struct Barrett_64 {
  u128 mod, mh, ml;

  explicit Barrett_64(u64 mod = 1) : mod(mod) {
    u128 m = u128(-1) / mod;
    if (m * mod + mod == u128(0)) ++m;
    mh = m >> 64;
    ml = m & u64(-1);
  }

  u64 umod() const { return mod; }

  u64 modulo(u128 x) {
    u128 z = (x & u64(-1)) * ml;
    z = (x & u64(-1)) * mh + (x >> 64) * ml + (z >> 64);
    z = (x >> 64) * mh + (z >> 64);
    x -= z * mod;
    return x < mod ? x : x - mod;
  }

  u64 mul(u64 a, u64 b) { return modulo(u128(a) * b); }
};

u32 mod_pow(int a, ll n, int mod) {
  assert(n >= 0);
  a = ((a %= mod) < 0 ? a + mod : a);
  if ((mod & 1) && (mod < (1 << 30))) {
    using mint = Mongomery_modint_32<202311021>;
    mint::set_mod(mod);
    return mint(a).pow(n).val();
  }
  Barrett bt(mod);
  int r = 1;
  while (n) {
    if (n & 1) r = bt.mul(r, a);
    a = bt.mul(a, a), n >>= 1;
  }
  return r;
}

u64 mod_pow_64(ll a, ll n, u64 mod) {
  assert(n >= 0);
  a = ((a %= mod) < 0 ? a + mod : a);
  if ((mod & 1) && (mod < (u64(1) << 62))) {
    using mint = Mongomery_modint_64<202311021>;
    mint::set_mod(mod);
    return mint(a).pow(n).val();
  }
  Barrett_64 bt(mod);
  ll r = 1;
  while (n) {
    if (n & 1) r = bt.mul(r, a);
    a = bt.mul(a, a), n >>= 1;
  }
  return r;
}

template <typename T>
struct Gaussian_Integer {
  T x, y;
  using G = Gaussian_Integer;

  Gaussian_Integer(T x = 0, T y = 0) : x(x), y(y) {}
  Gaussian_Integer(pair<T, T> p) : x(p.fi), y(p.se) {}

  T norm() const { return x * x + y * y; }
  G conjugate() const { return G(x, -y); }

  G &operator+=(const G &g) {
    x += g.x, y += g.y;
    return *this;
  }
  G &operator-=(const G &g) {
    x -= g.x, y -= g.y;
    return *this;
  }
  G &operator*=(const G &g) {
    tie(x, y) = mp(x * g.x - y * g.y, x * g.y + y * g.x);
    return *this;
  }
  G &operator/=(const G &g) {
    *this *= g.conjugate();
    T n = g.norm();
    x = floor(x + n / 2, n);
    y = floor(y + n / 2, n);
    return *this;
  }
  G &operator%=(const G &g) {
    auto q = G(*this) / g;
    q *= g;
    (*this) -= q;
    return *this;
  }
  G operator-() { return G(-x, -y); }
  G operator+(const G &g) { return G(*this) += g; }
  G operator-(const G &g) { return G(*this) -= g; }
  G operator*(const G &g) { return G(*this) *= g; }
  G operator/(const G &g) { return G(*this) /= g; }
  G operator%(const G &g) { return G(*this) %= g; }
  bool operator==(const G &g) { return (x == g.x && y == g.y); }

  static G gcd(G a, G b) {
    while (b.x != 0 || b.y != 0) {
      a %= b;
      swap(a, b);
    }
    return a;
  }

  G pow(ll n) const {
    assert(n >= 0);
    G ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  // (g,x,y) s.t ax+by=g
  static tuple<G, G, G> extgcd(G a, G b) {
    if (b.x != 0 || b.y != 0) {
      G q = a / b;
      auto [g, x, y] = extgcd(b, a - q * b);
      return {g, y, x - q * y};
    }
    return {a, G{1, 0}, G{0, 0}};
  }
};

pair<ll, ll> solve_norm_equation_prime(ll p) {
  using G = Gaussian_Integer<i128>;
  assert(p == 2 || p % 4 == 1);
  if (p == 2) return {1, 1};
  ll x = [&]() -> ll {
    ll x = 1;
    while (1) {
      ++x;
      ll pow_x = 1;
      if (p < (1 << 30)) {
        pow_x = mod_pow(x, (p - 1) / 4, p);
        if (pow_x * pow_x % p == p - 1) return pow_x;
      } else {
        pow_x = mod_pow_64(x, (p - 1) / 4, p);
        if (i128(pow_x) * pow_x % p == p - 1) return pow_x;
      }
    }
    return -1;
  }();
  G a(p, 0), b(x, 1);
  a = G::gcd(a, b);
  assert(a.norm() == p);
  return {a.x, a.y};
}

template <typename T>
vc<Gaussian_Integer<T>> solve_norm_equation_factor(vc<pair<ll, int>> pfs) {
  using G = Gaussian_Integer<T>;
  vc<G> res;
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3 && e % 2 == 1) return {};
  }

  res.eb(G(1, 0));
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3) {
      T pp = 1;
      FOR(e / 2) pp *= p;
      for (auto &&g: res) {
        g.x *= pp;
        g.y *= pp;
      }
      continue;
    }
    auto [pix, piy] = solve_norm_equation_prime(p);
    G pi(pix, piy);
    vc<G> pows(e + 1);
    pows[0] = G(1, 0);
    FOR(i, e) pows[i + 1] = pows[i] * pi;
    if (p == 2) {
      for (auto &&g: res) g *= pows[e];
      continue;
    }
    vc<G> pis(e + 1);
    FOR(j, e + 1) { pis[j] = pows[j] * (pows[e - j].conjugate()); }
    vc<G> new_res;
    new_res.reserve(len(res) * (e + 1));
    for (auto &&g: res) {
      for (auto &&a: pis) { new_res.eb(g * a); }
    }
    swap(res, new_res);
  }

  for (auto &&g: res) {
    while (g.x <= 0 || g.y < 0) { g = G(-g.y, g.x); }
  }
  return res;
}

// i128 を使うと N <= 10^{18} もできる
// ノルムがとれるように、2 乗してもオーバーフローしない型を使おう
// 0 <= arg < 90 となるもののみ返す。
// 単数倍は作らないので、使うときに気を付ける。
template <typename T>
vc<Gaussian_Integer<T>> solve_norm_equation(T N) {
  using G = Gaussian_Integer<T>;
  vc<G> res;
  if (N < 0) return {};
  if (N == 0) {
    res.eb(G(0, 0));
    return res;
  }
  auto pfs = factor(N);
  return solve_norm_equation_factor<T>(pfs);
}

void solve() {
  ll N;
  scanf("%lld", &N);
  if (N == 0) {
    printf("1\n");
    printf("0 0\n");
    return;
  }
  auto pfs = factor(N);

  vc<pair<ll, ll>> ANS;
  for (auto &g: solve_norm_equation_factor<i128>(pfs)) {
    ll x = g.x, y = g.y;
    FOR(4) {
      tie(x, y) = mp(-y, x);
      if (x >= 0 && y >= 0) ANS.eb(x, y);
    }
  }

  ll expected_ANS_cnt = 1;
  bool square = 1;
  for (auto &[p, e]: pfs) {
    if (e & 1) square = 0;
    if (p == 2) {};
    if (p % 4 == 1) { expected_ANS_cnt *= e + 1; }
    if (p % 4 == 3) { expected_ANS_cnt *= (e % 2 == 0 ? 1 : 0); }
  }
  if (square) expected_ANS_cnt++;
  assert(expected_ANS_cnt == len(ANS));

  printf("%lld\n", len(ANS));
  for (auto &[a, b]: ANS) { printf("%lld %lld\n", a, b); }
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
  return 0;
}
