#include <vector>
#include <tuple>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <cmath>

using namespace std;

using ll = long long;
using u32 = uint32_t;
using u64 = uint64_t;

template <class T>
using vc = vector<T>;

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a) - 1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a) - 1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b) - 1; i >= ll(a); --i)
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
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
  return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const U &A) {
  return std::accumulate(A.begin(), A.end(), T{});
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1) {
  int N = A.size();
  vector<T> B(N + 1);
  FOR(i, N) { B[i + 1] = B[i] + A[i]; }
  if (off == 0) B.erase(B.begin());
  return B;
}

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  static modint raw(u32 v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(u32 x) : val(x % umod) {}
  constexpr modint(u64 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
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
    if (n < 0) return inverse().pow(-n);
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
  // (n, r), r は 1 の 2^n 乗根
  static constexpr pair<int, int> ntt_info() {
    if (mod == 120586241) return {20, 74066978};
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 943718401) return {22, 663003469};
    if (mod == 998244353) return {23, 31};
    if (mod == 1004535809) return {21, 582313106};
    if (mod == 1012924417) return {21, 368093570};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

#ifdef FASTIO
template <int mod>
void rd(modint<mod> &x) {
  fastio::rd(x.val);
  x.val %= mod;
  // assert(0 <= x.val && x.val < mod);
}
template <int mod>
void wt(modint<mod> x) {
  fastio::wt(x.val);
}
#endif

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;
// END: mod/modint.hpp
#line 5 "main.cpp"
// BEGIN: nt/dirichlet.hpp
#line 1 "nt/dirichlet.hpp"
// BEGIN: nt/integer_kth_root.hpp
#line 1 "nt/integer_kth_root.hpp"
u64 integer_kth_root(u64 k, u64 a) {
  assert(k >= 1);
  if (a == 0 || a == 1 || k == 1) return a;
  if (k >= 64) return 1;
  if (k == 2) return sqrtl(a);
  if (a == u64(-1)) --a;
  struct S {
    u64 v;
    S &operator*=(const S &o) {
      v = v <= u64(-1) / o.v ? v * o.v : u64(-1);
      return *this;
    }
  };
  auto power = [&](S x, ll n) -> S {
    S v{1};
    while (n) {
      if (n & 1) v *= x;
      x *= x;
      n /= 2;
    }
    return v;
  };
  u64 res = pow(a, nextafter(1 / double(k), 0));
  while (power(S{res + 1}, k).v <= a) ++res;
  return res;
}

struct Dirichlet {
  u64 N;
  u32 t, sq, n;
  Dirichlet(u64 N) : N(N) {
    assert(N <= u64(1) << 50);
    sq = sqrtl(N);
    t = (u64(sq) * sq + sq <= N ? sq : sq - 1);
    n = t + sq + 1;
    // [0,1,...,t,N/sq,...,N/1] (t<sq の場合の sq も両対応)
  };

  inline u32 get_index(u64 d) { return (d <= t ? d : n - u32(double(N) / d)); }

  inline u64 get_floor(u32 i) { return (i <= t ? i : double(N) / (n - i)); }

  template <typename T, typename F>
  vc<T> gen_sum_table(F f) {
    vc<T> S(n);
    FOR(i, 1, n) S[i] = f(get_floor(i));
    return S;
  }

  template <typename T>
  vc<T> convolution(vc<T> F, vc<T> G) {
    assert(len(F) == n && len(G) == n);
    if (N == 1) return {T(0), F[1] * G[1]};
    vc<T> f(n), g(n);
    FOR(i, 1, n) f[i] = F[i] - F[i - 1];
    FOR(i, 1, n) g[i] = G[i] - G[i - 1];

    vc<T> H(n);
    u64 K = integer_kth_root(3, N);
    u64 S = K * K;
    // S 以下であるような商について
    for (u64 a = 1; a <= K; ++a) {
      H[(a * a <= sq ? a * a : n - N / (a * a))] += f[a] * g[a];
      if (a * (a + 1) <= t) {  // a * small = small
        u64 ub = t / a;
        for (u64 b = a + 1; b <= ub; ++b) {
          H[a * b] += f[a] * g[b] + f[b] * g[a];
        }
      }
      // a * small = large
      {
        u64 q = min<u64>(S / a, t);
        for (u64 b = max(a, t / a) + 1; b <= q; ++b) {
          H[n - N / (a * b)] += f[a] * g[b] + f[b] * g[a];
        }
      }
      // a * large = large
      if (N / sq <= S / a) {
        u64 p = N / (S / a + 1) + 1;
        for (u64 b = p; b <= sq; ++b) {
          H[n - N / (a * (N / b))] += f[a] * g[n - b] + g[a] * f[n - b];
        }
      }
    }
    FOR(i, 1, n) H[i] += H[i - 1];
    for (u64 z = 1; N / z > S; ++z) {
      u64 M = N / z;
      u64 ub = sqrtl(M);
      H[n - z] = 0;
      for (u64 a = 1; a <= ub; ++a) {
        int idx = get_index(M / a);
        H[n - z] += f[a] * G[idx] + g[a] * F[idx];
      }
      H[n - z] -= F[ub] * G[ub];
    }
    return H;
  }

  // G=H/F. T は 1/F[1] が正しく計算できてほしい.
  template <typename T>
  vc<T> div(vc<T> H, vc<T> F) {
    assert(len(F) == n && len(H) == n && F[1] != 0);
    if (N == 1) return {T(0), H[1] / F[1]};
    T c = T(1) / F[1];
    for (auto &x : F) x *= c;

    vc<T> f(n), g(n), h(n);
    FOR(i, 1, n) f[i] = F[i] - F[i - 1];
    FOR(i, 1, n) h[i] = H[i] - H[i - 1];

    u64 K = integer_kth_root(3, N);
    u64 S = max<u64>(sq, K * K);
    g[1] = H[1];

    for (u64 i = 2; i < n; ++i) {
      u64 a = get_floor(i);
      if (a > S) break;
      g[i] = h[i] - g[1] * f[i];
      if (a * a <= S) h[get_index(a * a)] -= f[i] * g[i];
      u64 ub = min(i - 1, S / a);
      FOR(b, 2, ub + 1) { h[get_index(a * b)] -= f[i] * g[b] + f[b] * g[i]; }
    }
    vc<T> G = cumsum<T>(g, 0);
    for (u64 z = N / (S + 1); z >= 1; --z) {
      G[n - z] = H[n - z] - g[1] * F[n - z];
      u64 M = N / z;
      u64 ub = sqrtl(M);
      G[n - z] += F[ub] * G[ub];
      for (u64 a = 2; a <= ub; ++a) {
        int idx = get_index(M / a);
        G[n - z] -= f[a] * G[idx] + g[a] * F[idx];
      }
    }
    for (auto &x : G) x *= c;
    c = T(1) / c;
    return G;
  }
};

using mint = modint998;
void solve() {
  ll N;
  scanf("%lld", &N);

  Dirichlet DIR(N);
  ll n = DIR.n;
  vc<mint> F(n);
  for (int i = 1; i < n; ++i) {
    int x;
    scanf("%d", &x);
    F[i] = x;
  }
  vc<mint> G(n, 1);
  G[0] = 0;
  F = DIR.div(G, F);
  for (int i = 1; i < n; ++i) {
    if (i > 1) printf(" ");
    printf("%u", F[i].val);
  }
  printf("\n");
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
}
