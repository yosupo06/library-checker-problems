#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <algorithm>

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

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define stoi stoll

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(vc<T>& que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <typename mint>
int count_terms(const vc<mint>& f) {
  int t = 0;
  FOR(i, len(f)) if (f[i] != mint(0))++ t;
  return t;
}

struct has_mod_impl {
  template <class T>
  static auto check(T&& x) -> decltype(x.get_mod(), std::true_type{});
  template <class T>
  static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

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
  constexpr modint(u128 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(i128 x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint& other) const { return val < other.val; }
  modint& operator+=(const modint& p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator-=(const modint& p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator*=(const modint& p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint& operator/=(const modint& p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint& p) const { return modint(*this) += p; }
  modint operator-(const modint& p) const { return modint(*this) -= p; }
  modint operator*(const modint& p) const { return modint(*this) *= p; }
  modint operator/(const modint& p) const { return modint(*this) /= p; }
  bool operator==(const modint& p) const { return val == p.val; }
  bool operator!=(const modint& p) const { return val != p.val; }
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
    if (mod == 120586241) return {20, 74066978};
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 943718401) return {22, 663003469};
    if (mod == 998244353) return {23, 31};
    if (mod == 1045430273) return {20, 363};
    if (mod == 1051721729) return {20, 330};
    if (mod == 1053818881) return {20, 2789};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;

template <class T, typename enable_if<!has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vector<T> ans(n + m - 1);
  FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  return ans;
}

template <class T, typename enable_if<has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vc<T> ans(n + m - 1);
  if (n <= 16 && (T::get_mod() < (1 << 30))) {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u64 sm = 0;
      for (int i = s; i < t; ++i) { sm += u64(a[i].val) * (b[k - i].val); }
      ans[k] = sm;
    }
  } else {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u128 sm = 0;
      for (int i = s; i < t; ++i) { sm += u64(a[i].val) * (b[k - i].val); }
      ans[k] = T::raw(sm % T::get_mod());
    }
  }
  return ans;
}

// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T>& f, const vc<T>& g) {
  const int thresh = 30;
  if (min(len(f), len(g)) <= thresh) return convolution_naive(f, g);
  int n = max(len(f), len(g));
  int m = ceil(n, 2);
  vc<T> f1, f2, g1, g2;
  if (len(f) < m) f1 = f;
  if (len(f) >= m) f1 = {f.begin(), f.begin() + m};
  if (len(f) >= m) f2 = {f.begin() + m, f.end()};
  if (len(g) < m) g1 = g;
  if (len(g) >= m) g1 = {g.begin(), g.begin() + m};
  if (len(g) >= m) g2 = {g.begin() + m, g.end()};
  vc<T> a = convolution_karatsuba(f1, g1);
  vc<T> b = convolution_karatsuba(f2, g2);
  FOR(i, len(f2)) f1[i] += f2[i];
  FOR(i, len(g2)) g1[i] += g2[i];
  vc<T> c = convolution_karatsuba(f1, g1);
  vc<T> F(len(f) + len(g) - 1);
  assert(2 * m + len(b) <= len(F));
  FOR(i, len(a)) F[i] += a[i], c[i] -= a[i];
  FOR(i, len(b)) F[2 * m + i] += b[i], c[i] -= b[i];
  if (c.back() == T(0)) c.pop_back();
  FOR(i, len(c)) if (c[i] != T(0)) F[m + i] += c[i];
  return F;
}

template <class mint>
void ntt(vector<mint>& a, bool inverse) {
  assert(mint::can_ntt());
  const int rank2 = mint::ntt_info().fi;
  const int mod = mint::get_mod();
  static array<mint, 30> root, iroot;
  static array<mint, 30> rate2, irate2;
  static array<mint, 30> rate3, irate3;

  assert(rank2 != -1 && len(a) <= (1 << max(0, rank2)));

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

template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
  if (a.empty() || b.empty()) return {};
  int n = int(a.size()), m = int(b.size());
  int sz = 1;
  while (sz < n + m - 1) sz *= 2;
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
vc<mint> convolution(const vc<mint>& a, const vc<mint>& b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
  return convolution_ntt(a, b);
}

template <typename mint>
vc<mint> fps_inv_sparse(const vc<mint>& f) {
  int N = len(f);
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> g(N);
  mint g0 = mint(1) / f[0];
  g[0] = g0;
  FOR(n, 1, N) {
    mint rhs = 0;
    for (auto&& [k, fk]: dat) {
      if (k > n) break;
      rhs -= fk * g[n - k];
    }
    g[n] = rhs * g0;
  }
  return g;
}

template <typename mint>
vc<mint> fps_inv_dense(const vc<mint>& F) {
  vc<mint> G = {mint(1) / F[0]};
  ll N = len(F), n = 1;
  G.reserve(N);
  while (n < N) {
    vc<mint> f(2 * n), g(2 * n);
    FOR(i, min(N, 2 * n)) f[i] = F[i];
    FOR(i, n) g[i] = G[i];
    ntt(f, false), ntt(g, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n) f[i] = 0;
    ntt(f, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n, min(N, 2 * n)) G.eb(-f[i]);
    n *= 2;
  }
  return G;
}

template <typename mint>
vc<mint> fps_inv(const vc<mint>& f) {
  assert(f[0] != mint(0));
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 160 : 820);
  return (n <= t ? fps_inv_sparse<mint>(f) : fps_inv_dense<mint>(f));
}

template <typename mint>
pair<vc<mint>, vc<mint>> poly_divmod(vc<mint> f, vc<mint> g) {
  assert(g.back() != 0);
  if (len(f) < len(g)) { return {{}, f}; }
  auto rf = f, rg = g;
  reverse(all(rf)), reverse(all(rg));
  ll deg = len(rf) - len(rg) + 1;
  rf.resize(deg), rg.resize(deg);
  rg = fps_inv(rg);
  auto q = convolution(rf, rg);
  q.resize(deg);
  reverse(all(q));
  auto h = convolution(q, g);
  FOR(i, len(f)) f[i] -= h[i];
  while (len(f) > 0 && f.back() == 0) f.pop_back();
  return {q, f};
}

// f^n mod g
template <typename mint>
vc<mint> poly_mod_pow(vc<mint> f, ll n, vc<mint>& g) {
  if (n == 0) return {1};
  if (n == 1) return f;
  vc<mint> F = poly_mod_pow(f, n / 2, g);
  F = convolution<mint>(F, F);
  F = poly_divmod(F, g).se;
  if (n & 1) {
    F = convolution<mint>(F, f);
    F = poly_divmod(F, g).se;
  }
  return F;
}

// https://people.eecs.berkeley.edu/~fateman/282/readings/yap-2.pdf
namespace half_gcd {
template <typename T>
using arr = array<vc<T>, 2>;

template <typename T>
using mat = array<vc<T>, 4>;

template <typename T>
void shrink(vc<T>& a) {
  while (len(a) && a.back() == 0) a.pop_back();
}

template <typename T>
vc<T> operator+(const vc<T>& a, const vc<T>& b) {
  vc<T> c(max(len(a), len(b)));
  FOR(i, len(a)) c[i] += a[i];
  FOR(i, len(b)) c[i] += b[i];
  shrink(c);
  return c;
}

template <typename T>
vc<T> operator-(const vc<T>& a, const vc<T>& b) {
  vc<T> c(max(len(a), len(b)));
  FOR(i, len(a)) c[i] += a[i];
  FOR(i, len(b)) c[i] -= b[i];
  shrink(c);
  return c;
}

template <typename T>
vc<T> operator*(const vc<T>& a, const vc<T>& b) {
  return convolution(a, b);
}

template <typename T>
mat<T> operator*(const mat<T>& A, const mat<T>& B) {
  return {A[0] * B[0] + A[1] * B[2], A[0] * B[1] + A[1] * B[3],
          A[2] * B[0] + A[3] * B[2], A[2] * B[1] + A[3] * B[3]};
}

template <typename T>
mat<T> step(const vc<T> q) {
  mat<T> Q;
  Q[1] = {1}, Q[2] = {1};
  Q[3] = Q[3] - q;
  return Q;
}

template <typename T>
arr<T> operator*(const mat<T>& A, const arr<T>& b) {
  return {A[0] * b[0] + A[1] * b[1], A[2] * b[0] + A[3] * b[1]};
}

template <typename T>
mat<T> hgcd(arr<T> a) {
  assert(len(a[0]) > len(a[1]) && len(a[1]) > 0);
  int m = len(a[0]) / 2;
  if (len(a[1]) <= m) {
    mat<T> M;
    M[0] = {1}, M[3] = {1};
    return M;
  }
  auto R = hgcd(arr<T>({vc<T>(a[0].begin() + m, a[0].end()),
                        vc<T>(a[1].begin() + m, a[1].end())}));
  a = R * a;
  if (len(a[1]) <= m) return R;
  mat<T> Q = step(poly_divmod(a[0], a[1]).fi);
  R = Q * R, a = Q * a;
  if (len(a[1]) <= m) return R;
  int k = 2 * m + 1 - len(a[0]);
  auto H = hgcd(arr<T>({vc<T>(a[0].begin() + k, a[0].end()),
                        vc<T>(a[1].begin() + k, a[1].end())}));
  return H * R;
}

template <typename T>
mat<T> cgcd(arr<T> a) {
  assert(a[0].size() > a[1].size() && !a[1].empty());
  auto m0 = hgcd(a);
  a = m0 * a;
  if (a[1].empty()) return m0;
  mat<T> Q = step(poly_divmod(a[0], a[1]).fi);
  m0 = Q * m0, a = Q * a;
  if (a[1].empty()) return m0;
  return cgcd(a) * m0;
}

// gcd == f * fi + g * gi となる (gcd, fi, gi)
template <typename T>
tuple<vc<T>, vc<T>, vc<T>> poly_extgcd(const vc<T>& f, const vc<T>& g) {
  mat<T> Q = step(poly_divmod(f, g).fi);
  auto m = Q;
  auto ap = Q * arr<T>{f, g};
  if (!ap[1].empty()) m = cgcd(ap) * m;
  return {f * m[0] + g * m[1], m[0], m[1]};
}

template <typename T>
vc<T> poly_gcd(vc<T> f, vc<T> g) {
  while (len(f) && f.back() == T(0)) POP(f);
  while (len(g) && g.back() == T(0)) POP(g);
  if (f.empty()) return g;
  if (g.empty()) return f;
  auto F = get<0>(poly_extgcd(f, g));
  T c = T(1) / F.back();
  for (auto& f: F) f *= c;
  return F;
}
} // namespace half_gcd
using half_gcd::poly_extgcd;
using half_gcd::poly_gcd;

u64 RNG_64() {
  static u64 x_ = 10150724397891781847ULL;
  x_ ^= x_ << 7;
  return x_ ^= x_ >> 9;
}
u64 RNG(u64 lim) { return RNG_64() % lim; }
ll RNG(ll l, ll r) { return l + RNG_64() % (r - l); }

// F(a)=0 を満たす a 全体を返す
// 昇順にソートして返すことに
template <typename mint>
vc<mint> finding_root_of_polynomial(vc<mint> F) {
  while (len(F) && F.back() == mint(0)) POP(F);
  assert(!F.empty());

  const int p = mint::get_mod();
  assert(p % 2 == 1);

  vc<mint> g = {0, 1};
  g = poly_mod_pow(g, p, F);
  if (len(g) <= 2) g.resize(2);
  g[1] -= 1;
  F = poly_gcd(F, g);

  // F は相異なる 1 次式の積
  vc<mint> ANS;
  auto dfs = [&](auto& dfs, vc<mint> F) -> void {
    if (len(F) == 1) return;
    if (len(F) == 2) {
      mint a = F[0], b = F[1];
      // a+bx=0
      ANS.eb((-a) / b);
      return;
    }
    vc<mint> g(2);
    g[0] = RNG(0, p), g[1] = 1;
    vc<mint> h = poly_mod_pow(g, (p - 1) / 2, F);
    if (h.empty()) { return dfs(dfs, F); }
    h[0] -= 1;
    vc<mint> f1 = poly_gcd(F, h);
    vc<mint> f2 = poly_divmod(F, f1).fi;
    dfs(dfs, f1), dfs(dfs, f2);
  };
  dfs(dfs, F);
  sort(all(ANS));
  return ANS;
}

template <typename T>
vc<T> convolution_all(vc<vc<T>>& polys) {
  if (len(polys) == 0) return {T(1)};
  while (1) {
    int n = len(polys);
    if (n == 1) break;
    int m = ceil(n, 2);
    FOR(i, m) {
      if (2 * i + 1 == n) {
        polys[i] = polys[2 * i];
      } else {
        polys[i] = convolution(polys[2 * i], polys[2 * i + 1]);
      }
    }
    polys.resize(m);
  }
  return polys[0];
}

// 相異なる 1 次式の積、重複度まあまああるかも
void test_1() {
  using mint = modint998;
  using poly = vc<mint>;
  int p = mint::get_mod();
  FOR(N, 50) {
    FOR(10) {
      vc<mint> S;
      FOR(10) S.eb(RNG(0, p));
      vc<poly> polys;
      vc<mint> roots;
      FOR(N) {
        mint a = S[RNG(0, 10)];
        roots.eb(a);
        polys.eb(poly({-mint(a), mint(1)}));
      }
      UNIQUE(roots);
      poly f = convolution_all(polys);
      auto ANS = finding_root_of_polynomial(f);
      sort(all(ANS));
      assert(roots == ANS);
    }
  }
}

// test_1 にもうひとつ N 次式をかける
void test_2() {
  using mint = modint998;
  using poly = vc<mint>;
  int p = mint::get_mod();
  FOR(N, 50) {
    FOR(10) {
      vc<mint> S;
      FOR(10) S.eb(RNG(0, p));
      vc<poly> polys;
      vc<mint> roots;
      FOR(N) {
        mint a = S[RNG(0, 10)];
        roots.eb(a);
        polys.eb(poly({-mint(a), mint(1)}));
      }
      UNIQUE(roots);
      poly f = convolution_all(polys);
      vc<mint> g(N + 1);
      FOR(i, N + 1) g[i] = RNG(0, p);
      f = convolution(f, g);
      auto ANS = finding_root_of_polynomial(f);
      for (auto& r: roots) { assert(binary_search(all(ANS), r)); }
    }
  }
}

using mint = modint998;

void solve() {
  int N;
  scanf("%d", &N);
  vc<mint> F(N + 1);
  FOR(n, N + 1) {
    int x;
    scanf("%d", &x);
    F[n] = x;
  }
  auto ANS = finding_root_of_polynomial(F);
  int n = len(ANS);
  printf("%d\n", n);
  FOR(i, n) {
    if (i) printf(" ");
    printf("%d", ANS[i].val);
  }
  printf("\n");
}

signed main() {
  // test_1();
  // test_2();
  solve();
  return 0;
}
