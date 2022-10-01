#include "testlib.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;

struct m64 {
  using i64 = int64_t;
  using u64 = uint64_t;
  using u128 = __uint128_t;

  inline static u64 m, r, n2; // r * m = -1 (mod 1<<64), n2 = 1<<128 (mod m)
  static void set_mod(u64 m) {
    assert(m < (1ull << 62));
    assert((m & 1) == 1);
    m64::m = m;
    n2 = -u128(m) % m;
    r = m;
    for (int i = 0; i < 5; ++i) r *= 2 - m * r;
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

bool primetest(const uint64_t x) {
  using u64 = uint64_t;
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

unsigned long RND() {
  static unsigned long x = 123456789, y = 362436069, z = 521288629,
                       w = 88675123;
  unsigned long t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;
  return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

ll rho(ll n, ll c) {
  m64::set_mod(n);
  assert(n > 1);
  const m64 cc(c);
  auto f = [&](m64 x) { return x * x + cc; };
  m64 x = 1, y = 2, z = 1, q = 1;
  ll g = 1;

  ll lg = 0;
  while ((1LL << (1 + lg)) <= n) ++lg;
  const ll m = 1LL << lg / 5;
  for (ll r = 1; g == 1; r <<= 1) {
    x = y;
    for (int i = 0; i < r; ++i) y = f(y);
    for (ll k = 0; k < r and g == 1; k += m) {
      z = y;
      for (int i = 0; i < min(m, r - k); ++i) y = f(y), q *= x - y;
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
  for (int i = 0; i < 100; ++i) {
    ll m = rho(n, RND() % n);
    if (primetest(m)) return m;
    n = m;
  }
  assert(false);
  return -1;
}

vector<pi> factor(ll n) {
  assert(n >= 1);
  vector<pi> pf;
  for (int p = 2; p < 100; ++p) {
    if (p * p > n) break;
    if (n % p == 0) {
      ll e = 0;
      do { n /= p, e += 1; } while (n % p == 0);
      pf.emplace_back(p, e);
    }
  }
  while (n > 1) {
    ll p = find_prime_factor(n);
    ll e = 0;
    do { n /= p, e += 1; } while (n % p == 0);
    pf.emplace_back(p, e);
  }
  sort(pf.begin(), pf.end());
  return pf;
}

vector<pi> factor_by_lpf(ll n, vector<int> &lpf) {
  vector<pi> res;
  while (n > 1) {
    int p = lpf[n];
    int e = 0;
    while (n % p == 0) {
      n /= p;
      ++e;
    }
    res.emplace_back(p, e);
  }
  return res;
}

ll mod_pow_long(ll a, ll n, ll mod) {
  using i128 = __int128;
  a %= mod;
  ll p = a;
  ll v = 1;
  while (n) {
    if (n & 1) v = i128(v) * p % mod;
    p = i128(p) * p % mod;
    n >>= 1;
  }
  return v;
}

bool check_primitive_root(ll p, ll r) {
  for (auto &&[q, k]: factor(p - 1)) {
    if (mod_pow_long(r, (p - 1) / q, p) == 1) return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  int Q = inf.readInt();
  for (int q = 0; q < Q; ++q) {
    ll p = inf.readLong();
    ll r = ouf.readLong(0, p - 1);
    if (!check_primitive_root(p, r)) {
      quitf(_wa, "'%lld' is not a primitive root modulo '%lld'", r, p);
    }
  }

  if (ouf.seekEof()) {
    quitf(_ok, "OK");
  } else {
    quitf(_wa, "Participant output contains extra tokens");
  }
}
