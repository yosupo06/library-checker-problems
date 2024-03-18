#include <vector>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <array>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

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
#define fi first
#define se second

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
    if (mod == 998244353) return {23, 31};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

using modint998 = modint<998244353>;

template <class T>
vc<T> convolution_naive(const vc<T> &a, const vc<T> &b) {
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
    FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  }
  return ans;
}

// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T> &f, const vc<T> &g) {
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
void ntt(vector<mint> &a, bool inverse) {
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
vc<mint> convolution(const vc<mint> &a, const vc<mint> &b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
  return convolution_ntt(a, b);
}

template <typename T>
vc<vc<T>> convolution2d(vc<vc<T>> &f, vc<vc<T>> &g) {
  auto shape = [&](vc<vc<T>> &f) -> pair<int, int> {
    ll H = len(f);
    ll W = (H == 0 ? 0 : len(f[0]));
    return {H, W};
  };
  auto [H1, W1] = shape(f);
  auto [H2, W2] = shape(g);
  ll H = H1 + H2 - 1;
  ll W = W1 + W2 - 1;

  vc<T> ff(H1 * W);
  vc<T> gg(H2 * W);
  FOR(x, H1) FOR(y, W1) ff[W * x + y] = f[x][y];
  FOR(x, H2) FOR(y, W2) gg[W * x + y] = g[x][y];
  auto hh = convolution(ff, gg);
  vc<vc<T>> h(H, vc<T>(W));
  FOR(x, H) FOR(y, W) h[x][y] = hh[W * x + y];
  return h;
}

// a^0, ..., a^N
template <typename mint>
vc<mint> powertable_1(mint a, ll N) {
  // table of a^i
  vc<mint> f(N + 1, 1);
  FOR(i, N) f[i + 1] = a * f[i];
  return f;
}

// f(x) -> f(x+c)
template <typename mint>
vc<mint> poly_taylor_shift(vc<mint> f, mint c) {
  ll N = len(f);
  FOR(i, N) f[i] *= fact<mint>(i);
  auto b = powertable_1<mint>(c, N);
  FOR(i, N) b[i] *= fact_inv<mint>(i);
  reverse(all(f));
  f = convolution(f, b);
  f.resize(N);
  reverse(all(f));
  FOR(i, N) f[i] *= fact_inv<mint>(i);
  return f;
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

template <typename mint>
vc<mint> middle_product_naive(vc<mint> &a, vc<mint> &b) {
  vc<mint> res(len(a) - len(b) + 1);
  FOR(i, len(res)) FOR(j, len(b)) res[i] += b[j] * a[i + j];
  return res;
}

// https://noshi91.hatenablog.com/entry/2024/03/16/224034
// O(Nlog^2N)
template <typename mint>
vc<mint> composition(vc<mint> f, vc<mint> g) {
  // 必要ではないが簡略化のために，[x^0]g=0 に帰着しておく.
  const int N = len(f) - 1;
  assert(len(f) == N + 1 && len(g) == N + 1);
  if (N == -1) return {};
  mint c = g[0];
  g[0] = 0;
  f = poly_taylor_shift<mint>(f, c);

  auto degree = [&](vvc<mint> &F) -> pair<int, int> {
    return {len(F) - 1, len(F[0]) - 1};
  };

  /*
  f, g は N 次とする.
  合成は (f_i) -> sum_i f_ig(x)^i である. これの転置を考える.
  (h_j) に対して [x^0]h(x^-1)sum_if_ig(x)^i = sum_if_i[x^0]h(x^{-1})g(x)^i
  であるから [x^N]rev_h(x)g(x)^i を計算するというのが転置である．
  したがって合成は [x^N]rev_h(x)g(x)^i 列挙の転置をとれば計算できる.

  転置問題は, 次のような反復により解ける：
  ・入力を reverse する.
  ・次を k=0,1,2,...,K で繰り返す（K=lg n 程度）.
  　・g だけから定まる何らかの G_k(x,y) と畳み込む
  　・適切な部分を抜き出す

  よって合成は次の計算による
  ・次を k=m,...,2,1,0 で繰り返す
  　・適切な部分に入れる
  　・G_k(x,y) との畳み込みの転置でうつす
  ・reverse して出力する.

  G_k(x,y) は k の昇順に計算できて，これを逆順に処理するため，
  ここでは再帰関数により実装する．
  */
  auto dfs = [&](auto &dfs, vvc<mint> G) -> vvc<mint> {
    auto [n, m] = degree(G);
    if (n == 0) {
      // [x^0]g=0 としていたので G=1 である.
      // 転置問題ではこの時点での多項式がそのまま出力となる.
      // よって入力をそのまま多項式に入れて返す.
      vv(mint, F, n + 1, m + 1);
      FOR(j, len(f)) F[0][j] = f[j];
      return F;
    }
    vvc<mint> G1 = G;
    FOR(i, n + 1) {
      if (i % 2 == 0) continue;
      FOR(j, m + 1) G1[i][j] = -G[i][j];
    }
    vvc<mint> G2 = convolution2d(G, G1);
    int n2 = n / 2;
    FOR(i, n2 + 1) G2[i] = G2[2 * i];
    G2.resize(n2 + 1);
    vvc<mint> F = dfs(dfs, G2);
    assert(degree(F) == degree(G2));
    // 転置問題では G1 と畳み込んだあと n の parity に応じた部分を抜き出す.
    // よってまず dfs の出力を抜き出す前の位置に入れて, 畳み込みの転置をとる.

    // 畳み込みの転置をとるとは何なのか.
    // (n,m) 次の多項式積 H(x,y) G(x,y)
    // H, G を適切に配置した (n+1)(2m+1)-1 次多項式を用意して
    // 畳み込んで 2(n+1)(2m+1)-2 次多項式を得る.
    // この適切な (2n,2m) 次多項式を抜き出す.
    // 転置をとると次のようになる.
    // F を適切に配置した (2n,2m) 次多項式を作る.
    // ここから 2(n+1)(2m+1)-2 次多項式を作る.
    // これと適切な多項式の middle product をとって
    // (n+1)(2m+1)-1 次多項式を得る.
    vc<mint> A(2 * (n + 1) * (2 * m + 1) - 1);
    FOR(i, len(F)) FOR(j, len(F[0])) {
      int i1 = 2 * i + (n % 2);
      int idx = i1 * (2 * m + 1) + j;
      A[idx] = F[i][j];
    }
    vc<mint> B((n + 1) * (2 * m + 1));
    FOR(i, n + 1) FOR(j, m + 1) {
      int idx = i * (2 * m + 1) + j;
      B[idx] = G1[i][j];
    }

    A = middle_product<mint>(A, B);
    assert(len(A) == (n + 1) * (2 * m + 1));
    vv(mint, res, n + 1, m + 1);
    FOR(i, n + 1) FOR(j, m + 1) {
      int idx = (2 * m + 1) * i + j;
      res[i][j] = A[idx];
    }
    return res;
  };
  vv(mint, G, N + 1, 2);
  G[0][0] = 1;
  FOR(i, N + 1) G[i][1] = -g[i];
  vvc<mint> F = dfs(dfs, G);
  assert(degree(F) == (pair<int, int>{N, 1}));
  vc<mint> ANS(N + 1);
  FOR(i, N + 1) ANS[i] = F[i][0];
  // 最後に reverse する
  reverse(all(ANS));
  return ANS;
}

using mint = modint998;

void solve() {
  int N;
  scanf("%d", &N);
  vc<mint> F(N), G(N);
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    F[i] = x;
  }
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    G[i] = x;
  }
  F = composition<mint>(F, G);
  FOR(i, N) {
    if (i) printf(" ");
    printf("%d", F[i].val);
  }
  printf("\n");
}

signed main() { solve(); }
