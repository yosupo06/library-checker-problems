#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <numeric>
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
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
  static_assert(r * mod == 1, "this code has bugs.");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)) {};

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
  constexpr mint operator+() const { return mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const {
    int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
    while (y > 0) {
      t = x / y;
      x -= t * y, u -= t * v;
      tmp = x, x = y, y = tmp;
      tmp = u, u = v, v = tmp;
    }
    return mint{u};
  }

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

// Prime Sieve {2, 3, 5, 7, 11, 13, 17, ...}
vector<int> prime_enumerate(int N) {
  vector<bool> sieve(N / 3 + 1, 1);
  for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn; p += d = 6 - d, i++) {
    if (!sieve[i]) continue;
    for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
             qe = sieve.size();
         q < qe; q += r = s - r)
      sieve[q] = 0;
  }
  vector<int> ret{2, 3};
  for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
    if (sieve[i]) ret.push_back(p);
  while (!ret.empty() && ret.back() > N) ret.pop_back();
  return ret;
}

// f(p, c) : f(p^c) の値を返す
template <typename T, T (*f)(long long, long long)>
struct mf_prefix_sum {
  using i64 = long long;

  i64 M, sq, s;
  vector<int> p;
  int ps;
  vector<T> buf;
  T ans;

  mf_prefix_sum(i64 m) : M(m) {
    assert(m <= 1e15);
    sq = sqrt(M);
    while (sq * sq > M) sq--;
    while ((sq + 1) * (sq + 1) <= M) sq++;

    if (M != 0) {
      i64 hls = md(M, sq);
      if (hls != 1 && md(M, hls - 1) == sq) hls--;
      s = hls + sq;

      p = prime_enumerate(sq);
      ps = p.size();
      ans = T{};
    }
  }

  // 素数の個数関数に関するテーブル
  vector<T> pi_table() {
    if (M == 0) return {};
    i64 hls = md(M, sq);
    if (hls != 1 && md(M, hls - 1) == sq) hls--;

    vector<i64> hl(hls);
    for (int i = 1; i < hls; i++) hl[i] = md(M, i) - 1;

    vector<int> hs(sq + 1);
    iota(begin(hs), end(hs), -1);

    int pi = 0;
    for (auto &x : p) {
      i64 x2 = i64(x) * x;
      i64 imax = min<i64>(hls, md(M, x2) + 1);
      for (i64 i = 1, ix = x; i < imax; ++i, ix += x) {
        hl[i] -= (ix < hls ? hl[ix] : hs[md(M, ix)]) - pi;
      }
      for (int n = sq; n >= x2; n--) hs[n] -= hs[md(n, x)] - pi;
      pi++;
    }

    vector<T> res;
    res.reserve(2 * sq + 10);
    for (auto &x : hl) res.push_back(x);
    for (int i = hs.size(); --i;) res.push_back(hs[i]);
    assert((int)res.size() == s);
    return res;
  }

  // 素数の prefix sum に関するテーブル
  vector<T> prime_sum_table() {
    if (M == 0) return {};
    i64 hls = md(M, sq);
    if (hls != 1 && md(M, hls - 1) == sq) hls--;

    vector<T> h(s);
    T inv2 = T{2}.inverse();
    for (int i = 1; i < hls; i++) {
      T x = md(M, i);
      h[i] = x * (x + 1) * inv2 - 1;
    }
    for (int i = 1; i <= sq; i++) {
      T x = i;
      h[s - i] = x * (x + 1) * inv2 - 1;
    }

    for (auto &x : p) {
      T xt = x;
      T pi = h[s - x + 1];
      i64 x2 = i64(x) * x;
      i64 imax = min<i64>(hls, md(M, x2) + 1);
      i64 ix = x;
      for (i64 i = 1; i < imax; ++i, ix += x) {
        h[i] -= ((ix < hls ? h[ix] : h[s - md(M, ix)]) - pi) * xt;
      }
      for (int n = sq; n >= x2; n--) {
        h[s - n] -= (h[s - md(n, x)] - pi) * xt;
      }
    }

    assert((int)h.size() == s);
    return h;
  }

  void dfs(int i, int c, i64 prod, T cur) {
    ans += cur * f(p[i], c + 1);
    i64 lim = md(M, prod);
    if (lim >= 1LL * p[i] * p[i]) dfs(i, c + 1, p[i] * prod, cur);
    cur *= f(p[i], c);
    ans += cur * (buf[idx(lim)] - buf[idx(p[i])]);
    int j = i + 1;
    // p_j < 2**21 -> (p_j)^3 < 2**63
    for (; j < ps && p[j] < (1 << 21) && 1LL * p[j] * p[j] * p[j] <= lim; j++) {
      dfs(j, 1, prod * p[j], cur);
    }
    for (; j < ps && 1LL * p[j] * p[j] <= lim; j++) {
      T sm = f(p[j], 2);
      int id1 = idx(md(lim, p[j])), id2 = idx(p[j]);
      sm += f(p[j], 1) * (buf[id1] - buf[id2]);
      ans += cur * sm;
    }
  }

  // fprime 破壊的
  T run(vector<T> &fprime) {
    if (M == 0) return {};
    set_buf(fprime);
    assert((int)buf.size() == s);
    ans = buf[idx(M)] + 1;
    for (int i = 0; i < ps; i++) dfs(i, 1, p[i], 1);
    return ans;
  }

  i64 md(i64 n, i64 d) { return double(n) / d; }
  i64 idx(i64 n) { return n <= sq ? s - n : md(M, n); }
  void set_buf(vector<T> &_buf) { swap(buf, _buf); }
};

using mint = LazyMontgomeryModInt<469762049>;

long long A, B;
mint f(long long p, long long e) { return A * e + B * p; }

int main() {
  int T;
  scanf("%d\n", &T);
  while (T--) {
    long long N;
    scanf("%lld %lld %lld\n", &N, &A, &B);
    mf_prefix_sum<mint, f> mps(N);
    vector<mint> h0 = mps.pi_table();
    vector<mint> h1 = mps.prime_sum_table();
    for (int i = 0; i < (int)h0.size(); i++) h0[i] = h0[i] * A + h1[i] * B;
    auto ans = mps.run(h0);
    printf("%d\n", (int)(ans.get()));
  }
}
