#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

template <class T>
using vc = vector<T>;

#define len(x) ll(x.size())
#define elif else if
#define eb emplace_back

int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define FOR4_R(i, a, b, c) for (ll i = (b)-1; i >= ll(a); i -= (c))
#define overload4(a, b, c, d, e, ...) e
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) \
  overload4(__VA_ARGS__, FOR4_R, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

template <int mod>
struct modint {
  static constexpr bool is_modint = true;
  int val;
  constexpr modint(const ll val = 0) noexcept
      : val(val >= 0 ? val % mod : (mod - (-val) % mod) % mod) {}
  bool operator<(const modint &other) const {
    return val < other.val;
  } // To use std::map
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= mod) val -= mod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += mod - p.val) >= mod) val -= mod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = (int)(1LL * val * p.val % mod);
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint(-val); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  modint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
};

struct ArbitraryModInt {
  static constexpr bool is_modint = true;
  int val;
  ArbitraryModInt() : val(0) {}
  ArbitraryModInt(ll y)
      : val(y >= 0 ? y % get_mod()
                   : (get_mod() - (-y) % get_mod()) % get_mod()) {}
  bool operator<(const ArbitraryModInt &other) const {
    return val < other.val;
  } // To use std::map<ArbitraryModInt, T>
  static int &get_mod() {
    static int mod = 0;
    return mod;
  }
  static void set_mod(int md) { get_mod() = md; }
  ArbitraryModInt &operator+=(const ArbitraryModInt &p) {
    if ((val += p.val) >= get_mod()) val -= get_mod();
    return *this;
  }
  ArbitraryModInt &operator-=(const ArbitraryModInt &p) {
    if ((val += get_mod() - p.val) >= get_mod()) val -= get_mod();
    return *this;
  }
  ArbitraryModInt &operator*=(const ArbitraryModInt &p) {
    long long a = (long long)val * p.val;
    int xh = (int)(a >> 32), xl = (int)a, d, m;
    asm("divl %4; \n\t" : "=a"(d), "=d"(m) : "d"(xh), "a"(xl), "r"(get_mod()));
    val = m;
    return *this;
  }
  ArbitraryModInt &operator/=(const ArbitraryModInt &p) {
    *this *= p.inverse();
    return *this;
  }
  ArbitraryModInt operator-() const { return ArbitraryModInt(get_mod() - val); }
  ArbitraryModInt operator+(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) += p;
  }
  ArbitraryModInt operator-(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) -= p;
  }
  ArbitraryModInt operator*(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) *= p;
  }
  ArbitraryModInt operator/(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) /= p;
  }
  bool operator==(const ArbitraryModInt &p) const { return val == p.val; }
  bool operator!=(const ArbitraryModInt &p) const { return val != p.val; }
  ArbitraryModInt inverse() const {
    int a = val, b = get_mod(), u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return ArbitraryModInt(u);
  }
  ArbitraryModInt pow(ll n) const {
    ArbitraryModInt ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
};

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;
using amint = ArbitraryModInt;

ll mod_inv(ll val, ll mod) {
  val %= mod;
  if (val < 0) val += mod;
  ll a = val, b = mod, u = 1, v = 0, t;
  while (b > 0) {
    t = a / b;
    swap(a -= t * b, b), swap(u -= t * v, v);
  }
  if (u < 0) u += mod;
  return u;
}

template <class T>
vector<T> convolution_naive(const vector<T> &a, const vector<T> &b) {
  int n = int(a.size()), m = int(b.size());
  vector<T> ans(n + m - 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) { ans[i + j] += a[i] * b[j]; }
  }
  return ans;
}

template <class mint>
struct ntt_info {
  static constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
  }

  static constexpr int rank2 = bsf_constexpr(mint::get_mod() - 1);
  array<mint, rank2 + 1> root;
  array<mint, rank2 + 1> iroot;
  array<mint, max(0, rank2 - 1)> rate2;
  array<mint, max(0, rank2 - 1)> irate2;
  array<mint, max(0, rank2 - 2)> rate3;
  array<mint, max(0, rank2 - 2)> irate3;

  ntt_info() {
    int g = primitive_root(mint::get_mod());
    root[rank2] = mint(g).pow((mint::get_mod() - 1) >> rank2);
    iroot[rank2] = mint(1) / root[rank2];
    for (int i = rank2 - 1; i >= 0; --i) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }

    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 2; i++) {
        rate2[i] = root[i + 2] * prod;
        irate2[i] = iroot[i + 2] * iprod;
        prod *= iroot[i + 2];
        iprod *= root[i + 2];
      }
    }
    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 3; i++) {
        rate3[i] = root[i + 3] * prod;
        irate3[i] = iroot[i + 3] * iprod;
        prod *= iroot[i + 3];
        iprod *= root[i + 3];
      }
    }
  }

  constexpr int primitive_root(int m) {
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 880803841) return 26;
    if (m == 998244353) return 3;
    if (m == 924844053) return 5;
    return -1;
  }
};

template <class mint>
void ntt(vector<mint> &a, bool inverse) {
  int n = int(a.size());
  int h = topbit(n);
  assert(n == 1 << h);
  static const ntt_info<mint> info;
  if (!inverse) {
    int len = 0; // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
    while (len < h) {
      if (h - len == 1) {
        int p = 1 << (h - len - 1);
        mint rot = 1;
        FOR(s, 1 << len) {
          int offset = s << (h - len);
          FOR(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * rot;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          rot *= info.rate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = info.root[2];
        for (int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            auto mod2 = 1ULL * mint::get_mod() * mint::get_mod();
            auto a0 = 1ULL * a[i + offset].val;
            auto a1 = 1ULL * a[i + offset + p].val * rot.val;
            auto a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;
            auto a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;
            auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val * imag.val;
            auto na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          rot *= info.rate3[topbit(~s & -~s)];
        }
        len += 2;
      }
    }
  } else {
    mint coef = mint(1) / mint(len(a));
    FOR(i, len(a)) a[i] *= coef;
    int len = h;
    while (len) {
      if (len == 1) {
        int p = 1 << (h - len);
        mint irot = 1;
        FOR(s, 1 << (len - 1)) {
          int offset = s << (h - len + 1);
          FOR(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p];
            a[i + offset] = l + r;
            a[i + offset + p]
                = (unsigned long long)(mint::get_mod() + l.val - r.val)
                  * irot.val;
            ;
          }
          irot *= info.irate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint irot = 1, iimag = info.iroot[2];
        FOR(s, (1 << (len - 2))) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for (int i = 0; i < p; i++) {
            auto a0 = 1ULL * a[i + offset + 0 * p].val;
            auto a1 = 1ULL * a[i + offset + 1 * p].val;
            auto a2 = 1ULL * a[i + offset + 2 * p].val;
            auto a3 = 1ULL * a[i + offset + 3 * p].val;

            auto a2na3iimag
                = 1ULL * mint((mint::get_mod() + a2 - a3) * iimag.val).val;

            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p]
                = (a0 + (mint::get_mod() - a1) + a2na3iimag) * irot.val;
            a[i + offset + 2 * p]
                = (a0 + a1 + (mint::get_mod() - a2) + (mint::get_mod() - a3))
                  * irot2.val;
            a[i + offset + 3 * p]
                = (a0 + (mint::get_mod() - a1) + (mint::get_mod() - a2na3iimag))
                  * irot3.val;
          }
          irot *= info.irate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  }
}

template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
  int n = int(a.size()), m = int(b.size());
  int sz = 1;
  while (sz < n + m - 1) sz *= 2;

  // sz = 2^k のときの高速化。分割統治的なやつで損しまくるので。
  if ((n + m - 3) <= sz / 2) {
    auto a_last = a.back(), b_last = b.back();
    a.pop_back(), b.pop_back();
    auto c = convolution(a, b);
    c.resize(n + m - 1);
    c[n + m - 2] = a_last * b_last;
    FOR(i, len(a)) c[i + len(b)] += a[i] * b_last;
    FOR(i, len(b)) c[i + len(a)] += b[i] * a_last;
    return c;
  }

  a.resize(sz), b.resize(sz);
  bool same = a == b;
  ntt(a, 0);
  if (same) {
    b = a;
  } else {
    ntt(b, 0);
  }
  FOR(i, sz) a[i] *= b[i];
  ntt(a, 1);
  a.resize(n + m - 1);
  return a;
}

template <typename mint>
vector<mint> convolution_garner(const vector<mint> &a, const vector<mint> &b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  static const long long nttprimes[] = {754974721, 167772161, 469762049};
  using mint0 = modint<754974721>;
  using mint1 = modint<167772161>;
  using mint2 = modint<469762049>;
  vc<mint0> a0(n), b0(m);
  vc<mint1> a1(n), b1(m);
  vc<mint2> a2(n), b2(m);
  FOR(i, n) a0[i] = a[i].val, a1[i] = a[i].val, a2[i] = a[i].val;
  FOR(i, m) b0[i] = b[i].val, b1[i] = b[i].val, b2[i] = b[i].val;
  auto c0 = convolution_ntt<mint0>(a0, b0);
  auto c1 = convolution_ntt<mint1>(a1, b1);
  auto c2 = convolution_ntt<mint2>(a2, b2);
  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];
  static const long long m0_inv_m1 = mint1(nttprimes[0]).inverse().val;
  static const long long m01_inv_m2 = mint2(m01).inverse().val;
  static const int mod = mint::get_mod();
  auto garner = [&](mint0 x0, mint1 x1, mint2 x2) -> mint {
    int r0 = x0.val, r1 = x1.val, r2 = x2.val;
    int v1 = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];
    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0]) * v1) * mint2(m01_inv_m2);
    return mint(r0 + 1LL * nttprimes[0] * v1 + m01 % mod * v2.val);
  };
  vc<mint> c(len(c0));
  FOR(i, len(c)) c[i] = garner(c0[i], c1[i], c2[i]);
  return c;
}

template <typename mint>
enable_if_t<is_same<mint, modint998>::value, vc<mint>> convolution(
    const vc<mint> &a, const vc<mint> &b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 60) return convolution_naive(a, b);
  return convolution_ntt(a, b);
}

template <typename mint>
enable_if_t<!is_same<mint, modint998>::value, vc<mint>> convolution(
    const vc<mint> &a, const vc<mint> &b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 60) return convolution_naive(a, b);
  return convolution_garner(a, b);
}

// calculate f(ar^k) for 0 <= k < m
// https://noshi91.github.io/algorithm-encyclopedia/chirp-z-transform#noredirect
template <typename mint>
vc<mint> multipoint_eval_on_geom_seq(vc<mint> f, mint a, mint r, int m) {
  assert(r != mint(0));
  const int n = len(f);
  if (n < 100) {
    vc<mint> g(n);
    FOR(i, m) {
      mint pow = 1;
      FOR(j, n) {
        g[i] += f[j] * pow;
        pow *= a;
      }
      a *= r;
    }
    return g;
  }
  // a == 1 に帰着
  mint pow_a = 1;
  FOR(i, n) f[i] *= pow_a, pow_a *= a;

  auto calc = [&](mint r, int m) -> vc<mint> {
    // r^{t_i} の計算
    vc<mint> res(m);
    mint pow = 1;
    res[0] = 1;
    FOR(i, m - 1) {
      res[i + 1] = res[i] * pow;
      pow *= r;
    }
    return res;
  };

  vc<mint> A = calc(r, n + m - 1), B = calc(r.inverse(), max(n, m));
  FOR(i, n) f[i] *= B[i];
  reverse(f.begin(), f.end());
  f = convolution(f, A);
  f = {f.begin() + n - 1, f.end()};
  f.resize(m);
  FOR(i, m) f[i] *= B[i];
  return f;
}

u64 RNG_64() {
  static u64 x_ = 10150724397891781847ULL;
  x_ ^= x_ << 7;
  return x_ ^= x_ >> 9;
}

u64 RNG(u64 lim) { return RNG_64() % lim; }

ll RNG(ll l, ll r) { return l + RNG_64() % (r - l); }

struct m64 {
  using i64 = ll;
  using u128 = __uint128_t;

  inline static u64 m, r, n2; // r * m = -1 (mod 1<<64), n2 = 1<<128 (mod m)
  static void set_mod(u64 m) {
    assert(m < (1ull << 62));
    assert((m & 1) == 1);
    m64::m = m;
    n2 = -u128(m) % m;
    r = m;
    FOR(_, 5) r *= 2 - m * r;
    r = -r;
    assert(r * m == -1ull);
  }
  static u64 reduce(u128 b) { return (b + u128(u64(b) * r) * m) >> 64; }

  u64 x;
  m64() : x(0) {}
  m64(u64 x) : x(reduce(u128(x) * n2)){};
  u64 val() const {
    u64 y = reduce(x);
    return y >= m ? y - m : y;
  }
  m64 &operator+=(m64 y) {
    x += y.x - (m << 1);
    x = (i64(x) < 0 ? x + (m << 1) : x);
    return *this;
  }
  m64 &operator-=(m64 y) {
    x -= y.x;
    x = (i64(x) < 0 ? x + (m << 1) : x);
    return *this;
  }
  m64 &operator*=(m64 y) {
    x = reduce(u128(x) * y.x);
    return *this;
  }
  m64 operator+(m64 y) const { return m64(*this) += y; }
  m64 operator-(m64 y) const { return m64(*this) -= y; }
  m64 operator*(m64 y) const { return m64(*this) *= y; }
  bool operator==(m64 y) const {
    return (x >= m ? x - m : x) == (y.x >= m ? y.x - m : y.x);
  }
  bool operator!=(m64 y) const { return not operator==(y); }
  m64 pow(u64 n) const {
    m64 y = 1, z = *this;
    for (; n; n >>= 1, z *= z)
      if (n & 1) y *= z;
    return y;
  }
};

bool primetest(const u64 x) {
  if (x == 2 or x == 3 or x == 5 or x == 7) return true;
  if (x % 2 == 0 or x % 3 == 0 or x % 5 == 0 or x % 7 == 0) return false;
  if (x < 121) return x > 1;
  const u64 d = (x - 1) >> __builtin_ctzll(x - 1);
  m64::set_mod(x);
  const m64 one(1), minus_one(x - 1);
  auto ok = [&](u64 a) {
    auto y = m64(a).pow(d);
    u64 t = d;
    while (y != one and y != minus_one and t != x - 1) y *= y, t <<= 1;
    if (y != minus_one and t % 2 == 0) return false;
    return true;
  };
  if (x < (1ull << 32)) {
    for (u64 a: {2, 7, 61})
      if (not ok(a)) return false;
  } else {
    for (u64 a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if (x <= a) return true;
      if (not ok(a)) return false;
    }
  }
  return true;
}

ll gcd(ll a, ll b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

ll rho(ll n, ll c) {
  m64::set_mod(n);
  assert(n > 1);
  const m64 cc(c);
  auto f = [&](m64 x) { return x * x + cc; };
  m64 x = 1, y = 2, z = 1, q = 1;
  ll g = 1;
  const ll m = 1LL << (topbit(n) / 5); // ?
  for (ll r = 1; g == 1; r <<= 1) {
    x = y;
    FOR(_, r) y = f(y);
    for (ll k = 0; k < r and g == 1; k += m) {
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
  FOR(_, 100) {
    ll m = rho(n, RNG(n));
    if (primetest(m)) return m;
    n = m;
  }
  assert(false);
  return -1;
}

vc<pair<ll, int>> factor(ll n) {
  assert(n >= 1);
  vc<pair<ll, int>> pf;
  FOR3(p, 2, 100) {
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
  sort(pf.begin(), pf.end());
  return pf;
}

ll mod_pow(ll a, ll n, int mod) {
  a = a % mod;
  ll p = a;
  ll v = 1;
  while (n) {
    if (n & 1) v = v * p % mod;
    p = p * p % mod;
    n >>= 1;
  }
  return v;
}

int primitive_root(int p) {
  auto pf = factor(p - 1);
  auto is_ok = [&](int g) -> bool {
    for (auto &&[q, e]: pf)
      if (mod_pow(g, (p - 1) / q, p) == 1) return false;
    return true;
  };
  FOR3(x, 1, p) {
    if (is_ok(x)) return x;
  }
  return -1;
}

using mint = amint;

void solve() {
  int p, K;
  scanf("%d %d", &p, &K);
  mint::set_mod(p);
  mint r = primitive_root(p);
  mint ir = r.inverse();

  vc<int> ns(K);
  vc<mint> root(K), iroot(K);
  FOR(k, K) scanf("%d", &(ns[k]));

  int N = 1;
  for (auto &&n: ns) N *= n;

  FOR(k, K) { root[k] = r.pow((p - 1) / ns[k]); }
  FOR(k, K) { iroot[k] = ir.pow((p - 1) / ns[k]); }

  vc<mint> f(N), g(N);
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    f[i] = x;
  }
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    g[i] = x;
  }

  int step = 1;
  FOR(k, K) {
    int n = ns[k];
    FOR(i, N) if (i % (step * n) < step) {
      vc<mint> a(n), b(n);
      FOR(j, n) {
        a[j] = f[i + step * j];
        b[j] = g[i + step * j];
      }
      a = multipoint_eval_on_geom_seq(a, mint(1), root[k], n);
      b = multipoint_eval_on_geom_seq(b, mint(1), root[k], n);
      FOR(j, n) {
        f[i + step * j] = a[j];
        g[i + step * j] = b[j];
      }
    }
    step *= n;
  }

  FOR(i, N) f[i] *= g[i];

  step = 1;
  FOR(k, K) {
    int n = ns[k];
    FOR(i, N) if (i % (step * n) < step) {
      vc<mint> a(n);
      FOR(j, n) { a[j] = f[i + step * j]; }
      a = multipoint_eval_on_geom_seq(a, mint(1), iroot[k], n);
      FOR(j, n) { f[i + step * j] = a[j]; }
    }
    step *= n;
  }

  mint cf = mint(N).inverse();
  for (auto &&x: f) x *= cf;

  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    printf("%d", f[i].val);
  }
  printf("\n");
}

signed main() {
  solve();

  return 0;
}
