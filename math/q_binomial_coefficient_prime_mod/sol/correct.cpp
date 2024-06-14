#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <array>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;

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

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}

template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (len(dat) <= n) {
    int k = len(dat);
    int q = (mod + k - 1) / k;
    dat.eb(dat[k * q - mod] * mint::raw(q));
  }
  return dat[n];
}

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * mint::raw(len(dat)));
  return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
  static vector<mint> dat = {1, 1};
  if (n < 0) return mint(0);
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * inv<mint>(len(dat)));
  return dat[n];
}

template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
  return (mint(1) * ... * fact_inv<mint>(xs));
}

template <typename mint, class Head, class... Tail>
mint multinomial(Head&& head, Tail&&... tail) {
  return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

template <typename mint>
mint C(ll n, ll k) {
  assert(n >= 0);
  if (k < 0 || n < k) return 0;
  return multinomial<mint>(n, k, n - k);
}

struct Barrett {
  u32 m;
  u64 im;
  explicit Barrett(u32 m = 1) : m(m), im(u64(-1) / m + 1) {}
  u32 umod() const { return m; }
  u32 modulo(u64 z) {
    // if (m == 1) return 0;
    // u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    // u64 y = x * m;
    // return (z - y + (z < y ? m : 0));
    return z % m;
  }
  u64 floor(u64 z) {
    // if (m == 1) return z;
    // u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    // u64 y = x * m;
    // return (z < y ? x - 1 : x);
    return z / m;
  }
  pair<u64, u32> divmod(u64 z) {
    // if (m == 1) return {z, 0};
    // u64 x = (u64)(((unsigned __int128)(z)*im) >> 64);
    // u64 y = x * m;
    // if (z < y) return {x - 1, z - y + m};
    // return {x, z - y};
    return {z / m, z % m};
  }
  u32 mul(u32 a, u32 b) { return modulo(u64(a) * b); }
};

template <int id>
struct Dynamic_Modint {
  static constexpr bool is_modint = true;
  using mint = Dynamic_Modint;
  u32 val;
  static Barrett bt;
  static u32 umod() { return bt.umod(); }

  static int get_mod() { return (int)(bt.umod()); }
  static void set_mod(int m) {
    assert(1 <= m);
    bt = Barrett(m);
  }

  static Dynamic_Modint raw(u32 v) {
    Dynamic_Modint x;
    x.val = v;
    return x;
  }
  Dynamic_Modint() : val(0) {}
  Dynamic_Modint(u32 x) : val(bt.modulo(x)) {}
  Dynamic_Modint(u64 x) : val(bt.modulo(x)) {}
  Dynamic_Modint(int x) : val((x %= get_mod()) < 0 ? x + get_mod() : x) {}
  Dynamic_Modint(ll x) : val((x %= get_mod()) < 0 ? x + get_mod() : x) {}

  mint& operator+=(const mint& rhs) {
    val = (val += rhs.val) < umod() ? val : val - umod();
    return *this;
  }
  mint& operator-=(const mint& rhs) {
    val = (val += umod() - rhs.val) < umod() ? val : val - umod();
    return *this;
  }
  mint& operator*=(const mint& rhs) {
    val = bt.mul(val, rhs.val);
    return *this;
  }
  mint& operator/=(const mint& rhs) { return *this = *this * rhs.inverse(); }
  mint operator-() const { return mint() - *this; }
  mint pow(ll n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x, n >>= 1;
    }
    return r;
  }
  mint inverse() const {
    int x = val, mod = get_mod();
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    if (u < 0) u += mod;
    return u;
  }

  friend mint operator+(const mint& lhs, const mint& rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint& lhs, const mint& rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint& lhs, const mint& rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint& lhs, const mint& rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint& lhs, const mint& rhs) {
    return lhs.val == rhs.val;
  }
  friend bool operator!=(const mint& lhs, const mint& rhs) {
    return lhs.val != rhs.val;
  }
  static pair<int, int>& get_ntt() {
    static pair<int, int> p = {-1, -1};
    return p;
  }
};

using dmint = Dynamic_Modint<-1>;
template <int id>
Barrett Dynamic_Modint<id>::bt;

template <typename mint>
vc<mint> all_inverse(vc<mint>& X) {
  for (auto&& x: X) assert(x != mint(0));
  int N = len(X);
  vc<mint> res(N + 1);
  res[0] = mint(1);
  FOR(i, N) res[i + 1] = res[i] * X[i];
  mint t = res.back().inverse();
  res.pop_back();
  FOR_R(i, N) {
    res[i] *= t;
    t *= X[i];
  }
  return res;
}

template <typename mint>
struct q_Analogue {
  const mint q;
  const int LIM;
  int D;
  vc<mint> factorial, ifactorial;

  q_Analogue(mint q, int LIM) : q(q), LIM(LIM) {
    assert(LIM < mint::get_mod());
    build();
  }

  void build() {
    factorial.reserve(LIM + 1);
    factorial.eb(1);
    mint x = 1;
    FOR(i, 1, LIM + 1) {
      if (x == mint(0)) break;
      factorial.eb(factorial.back() * x);
      x = q * x + mint(1);
    }
    ifactorial = all_inverse(factorial);
    D = len(factorial);
  }

  mint fact(int N) {
    assert(0 <= N && N <= LIM);
    return (N < D ? factorial[N] : mint(0));
  }
  mint fact_inv(int N) {
    assert(0 <= N && N < D);
    return (N < D ? ifactorial[N] : mint(0));
  }
  mint binom(int N, int K) {
    assert(0 <= N && N <= LIM);
    if (K < 0 || K > N) return mint(0);
    if (N < D) return factorial[N] * ifactorial[K] * ifactorial[N - K];
    auto [n1, n2] = divmod(N, D);
    auto [k1, k2] = divmod(K, D);
    return C<mint>(n1, k1) * binom(n2, k2);
  }
};

void solve() {
  int T, p, q;
  scanf("%d %d %d", &T, &p, &q);
  using mint = dmint;
  mint::set_mod(p);
  int lim = min(p - 1, 10'100'100);
  q_Analogue<mint> X(q, lim);

  FOR(T) {
    int n, k;
    scanf("%d %d", &n, &k);
    mint ans = X.binom(n, k);
    printf("%d\n", ans.val);
  }
}

signed main() {
  solve();
  return 0;
}
