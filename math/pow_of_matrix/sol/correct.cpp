#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = unsigned __int128;

using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

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
  static constexpr pair<int, int> ntt_info() {
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

using modint998 = modint<998244353>;

template <typename T>
vc<vc<T>> matrix_mul(const vc<vc<T>> &A, const vc<vc<T>> &B, int N1 = -1,
                     int N2 = -1, int N3 = -1) {
  if (N1 == -1) { N1 = len(A), N2 = len(B), N3 = len(B[0]); }
  vv(u32, b, N3, N2);
  FOR(i, N2) FOR(j, N3) b[j][i] = B[i][j].val;
  vv(T, C, N1, N3);

  FOR(i, N1) FOR(j, N3) {
    u128 sm = 0;
    FOR(m, N2) sm += u64(A[i][m].val) * b[j][m];
    C[i][j] = T::raw(sm % (T::get_mod()));
  }
  return C;
}

template <typename T>
vc<vc<T>> matrix_pow(vc<vc<T>> A, ll n) {
  int N = len(A);
  vv(T, ret, N, N);
  FOR(i, N) ret[i][i] = T(1);
  while (n) {
    if (n & 1) ret = matrix_mul(ret, A, N, N, N);
    n /= 2;
    if (n) A = matrix_mul(A, A, N, N, N);
  }
  return ret;
}

using mint = modint998;

void solve() {
  ll N, K;
  scanf("%lld %lld", &N, &K);
  vv(mint, A, N, N);
  FOR(i, N) FOR(j, N) {
    int x;
    scanf("%d", &x);
    A[i][j] = x;
  }
  A = matrix_pow(A, K);
  FOR(i, N) {
    FOR(j, N) {
      if (j) printf(" ");
      printf("%d", A[i][j].val);
    }
    printf("\n");
  }
}

signed main() {
  solve();
  return 0;
}
