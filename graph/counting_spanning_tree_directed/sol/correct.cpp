#include <vector>
#include <cassert>
#include <cstdio>
#include <array>
#include <algorithm>

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

template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
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
};

using modint998 = modint<998244353>;

int det_mod(vvc<int> A, int mod) {
  // Barrett bt(mod);
  const int n = len(A);
  ll det = 1;
  FOR(i, n) {
    FOR(j, i, n) {
      if (A[j][i] == 0) continue;
      if (i != j) { swap(A[i], A[j]), det = mod - det; }
      break;
    }
    FOR(j, i + 1, n) {
      while (A[i][i] != 0) {
        ll c = mod - A[j][i] / A[i][i];
        FOR_R(k, i, n) { A[j][k] = (A[j][k] + A[i][k] * c) % mod; }
        swap(A[i], A[j]), det = mod - det;
      }
      swap(A[i], A[j]), det = mod - det;
    }
  }
  FOR(i, n) det = (det * A[i][i]) % mod;
  return det % mod;
}

template <typename mint>
mint det(vvc<mint> &A) {
  const int n = len(A);
  vv(int, B, n, n);
  FOR(i, n) FOR(j, n) B[i][j] = A[i][j].val;
  return det_mod(B, mint::get_mod());
}

using mint = modint998;

void solve() {
  int N, M, r;
  scanf("%d %d %d\n", &N, &M, &r);
  vv(mint, mat, N, N);
  FOR(M) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    // convert to in-tree setting
    swap(a, b);
    mat[a][a] += 1, mat[a][b] -= 1;
  }
  FOR(i, N) { mat[i].erase(mat[i].begin() + r); }
  mat.erase(mat.begin() + r);
  mint ANS = det(mat);
  printf("%d\n", ANS.val);
}

signed main() {
  solve();
  return 0;
}
