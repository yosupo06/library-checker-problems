#include <vector>
#include <cstdio>
#include <cassert>
#include <array>
#include <algorithm>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

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

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

template <int mod>
struct modint {
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
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 998244353) return {23, 31};
    if (mod == 1045430273) return {20, 363};
    if (mod == 1051721729) return {20, 330};
    if (mod == 1053818881) return {20, 2789};
    return {-1, -1};
  }
};

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;

template <class mint>
void ntt(vector<mint> &a, bool inverse) {
  static constexpr int rank2 = mint::ntt_info().fi;
  static constexpr int mod = mint::get_mod();
  static_assert(rank2 != -1);
  static array<mint, rank2 + 1> root;
  static array<mint, rank2 + 1> iroot;
  static array<mint, max(0, rank2 - 1)> rate2, irate2;
  static array<mint, max(0, rank2 - 2)> rate3, irate3;
  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    root[rank2] = mint::ntt_info().se;
    iroot[rank2] = mint(1) / root[rank2];
    FOR_R(i, rank2) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    mint prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 2; i++) {
      rate2[i] = root[i + 2] * prod;
      irate2[i] = iroot[i + 2] * iprod;
      prod *= iroot[i + 2];
      iprod *= root[i + 2];
    }
    prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 3; i++) {
      rate3[i] = root[i + 3] * prod;
      irate3[i] = iroot[i + 3] * iprod;
      prod *= iroot[i + 3];
      iprod *= root[i + 3];
    }
  }

  int n = int(a.size());
  int h = topbit(n);
  assert(n == 1 << h);
  if (!inverse) {
    int len = 0;
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
          rot *= rate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = root[2];
        for (int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            u64 mod2 = u64(mod) * mod;
            u64 a0 = a[i + offset].val;
            u64 a1 = u64(a[i + offset + p].val) * rot.val;
            u64 a2 = u64(a[i + offset + 2 * p].val) * rot2.val;
            u64 a3 = u64(a[i + offset + 3 * p].val) * rot3.val;
            u64 a1na3imag = (a1 + mod2 - a3) % mod * imag.val;
            u64 na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          rot *= rate3[topbit(~s & -~s)];
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
            u64 l = a[i + offset].val;
            u64 r = a[i + offset + p].val;
            a[i + offset] = l + r;
            a[i + offset + p] = (mod + l - r) * irot.val;
          }
          irot *= irate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint irot = 1, iimag = iroot[2];
        FOR(s, (1 << (len - 2))) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for (int i = 0; i < p; i++) {
            u64 a0 = a[i + offset + 0 * p].val;
            u64 a1 = a[i + offset + 1 * p].val;
            u64 a2 = a[i + offset + 2 * p].val;
            u64 a3 = a[i + offset + 3 * p].val;
            u64 x = (mod + a2 - a3) * iimag.val % mod;
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] = (a0 + mod - a1 + x) * irot.val;
            a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * irot2.val;
            a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * irot3.val;
          }
          irot *= irate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  }
}

template <typename mint>
vc<mint> middle_product_naive(vc<mint> &a, vc<mint> &b) {
  vc<mint> res(len(a) - len(b) + 1);
  FOR(i, len(res)) FOR(j, len(b)) res[i] += b[j] * a[i + j];
  return res;
}

// n, m 次多項式 (n>=m) a, b → n-m 次多項式 c
// c[i] = sum_j b[j]a[i+j]
template <typename mint>
vc<mint> middle_product(vc<mint> &a, vc<mint> &b) {
  assert(len(a) >= len(b));
  if (b.empty()) return vc<mint>(len(a) - len(b) + 1);
  if (min(len(b), len(a) - len(b) + 1) <= 60) {
    return middle_product_naive(a, b);
  }
  if constexpr (mint::ntt_info().fi == -1) {
    return middle_product_garner(a, b);
  } else {
    int n = 1 << __lg(2 * len(a) - 1);
    vc<mint> fa(n), fb(n);
    copy(a.begin(), a.end(), fa.begin());
    copy(b.rbegin(), b.rend(), fb.begin());
    ntt(fa, 0), ntt(fb, 0);
    FOR(i, n) fa[i] *= fb[i];
    ntt(fa, 1);
    fa.resize(len(a));
    fa.erase(fa.begin(), fa.begin() + len(b) - 1);
    return fa;
  }
}

template <class T>
vector<T> convolution_naive(const vector<T> &a, const vector<T> &b) {
  int n = int(a.size()), m = int(b.size());
  vector<T> ans(n + m - 1);
  if (n < m) {
    FOR(j, m) FOR(i, n) ans[i + j] += a[i] * b[j];
  } else {
    FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  }
  return ans;
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
enable_if_t<is_same<mint, modint998>::value, vc<mint>> convolution(
    const vc<mint> &a, const vc<mint> &b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 60) return convolution_naive(a, b);
  return convolution_ntt(a, b);
}

template <typename mint>
vc<mint> all_inverse(vc<mint> &X) {
  for (auto &&x: X) assert(x != mint(0));
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

// Y[i] = f(ar^i)
template <typename mint>
vc<mint> multipoint_interpolate_on_geom_seq(vc<mint> Y, mint a, mint r) {
  const int n = len(Y);
  if (n == 0) return {};
  if (n == 1) return {Y[0]};
  assert(r != mint(0));
  mint ir = r.inverse();

  vc<mint> POW(n + n - 1), tPOW(n + n - 1);
  POW[0] = tPOW[0] = mint(1);
  FOR(i, n + n - 2) POW[i + 1] = POW[i] * r, tPOW[i + 1] = tPOW[i] * POW[i];

  vc<mint> iPOW(n + n - 1), itPOW(n + n - 1);
  iPOW[0] = itPOW[0] = mint(1);
  FOR(i, n) iPOW[i + 1] = iPOW[i] * ir, itPOW[i + 1] = itPOW[i] * iPOW[i];

  // prod_[1,i] 1-r^k
  vc<mint> S(n + 1);
  S[0] = mint(1);
  FOR(i, 1, n + 1) S[i] = S[i - 1] * (mint(1) - POW[i]);
  vc<mint> iS = all_inverse<mint>(S);

  FOR(i, n) {
    Y[i] = Y[i] * tPOW[n - 1 - i] * itPOW[n - 1] * iS[i] * iS[n - 1 - i];
    if (i % 2 == 1) Y[i] = -Y[i];
  }

  // sum_i Y[i] / 1-r^ix
  FOR(i, n) Y[i] *= itPOW[i];
  vc<mint> f = middle_product(tPOW, Y);
  FOR(i, n) f[i] *= itPOW[i];

  // prod 1-r^ix
  vc<mint> g(n);
  FOR(i, n) {
    g[i] = tPOW[i] * S[n] * iS[i] * iS[n - i];
    if (i % 2 == 1) g[i] = -g[i];
  }
  f = convolution<mint>(f, g);
  f.resize(n);

  reverse(all(f));
  mint ia = a.inverse();
  mint pow = 1;
  FOR(i, n) f[i] *= pow, pow *= ia;
  return f;
}

using mint = modint998;

void solve() {
  int N, a, r;
  scanf("%d %d %d", &N, &a, &r);
  vc<mint> Y(N);
  for (int i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);
    Y[i] = x;
  }
  vc<mint> f = multipoint_interpolate_on_geom_seq<mint>(Y, a, r);

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