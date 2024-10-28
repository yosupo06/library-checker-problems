#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

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
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
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
  static constexpr int get_mod() { return mod; }
};

using modint998 = modint<998244353>;

template <typename T>
vc<vc<T>> matrix_mul(const vc<vc<T>> &A, const vc<vc<T>> &B, int N1 = -1, int N2 = -1, int N3 = -1) {
  if (N1 == -1) { N1 = len(A), N2 = len(B), N3 = len(B[0]); }
  vvc<T> b(N2, vc<T>(N3));
  FOR(i, N2) FOR(j, N3) b[j][i] = B[i][j];
  vvc<T> C(N1, vc<T>(N3));
  FOR(n, N1) FOR(m, N2) FOR(k, N3) C[n][k] += A[n][m] * b[k][m];
  return C;
}

// (det, invA) をかえす
template <typename T>
pair<T, vc<vc<T>>> matrix_inv(vc<vc<T>> A) {
  T det = 1;
  int N = len(A);
  vvc<T> B(N, vc<T>(N));
  FOR(n, N) B[n][n] = 1;
  FOR(i, N) {
    FOR(k, i, N) if (A[k][i] != 0) {
      if (k != i) {
        swap(A[i], A[k]), swap(B[i], B[k]);
        det = -det;
      }
      break;
    }
    if (A[i][i] == 0) return {T(0), {}};
    T c = T(1) / A[i][i];
    det *= A[i][i];
    FOR(j, i, N) A[i][j] *= c;
    FOR(j, N) B[i][j] *= c;
    FOR(k, N) if (i != k) {
      T c = A[k][i];
      FOR(j, i, N) A[k][j] -= A[i][j] * c;
      FOR(j, N) B[k][j] -= B[i][j] * c;
    }
  }
  return {det, B};
}

using mint = modint998;

void out(int n, vector<vector<mint>> a) {
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d", a[i][j].val);
      if (j + 1 != n) printf(" ");
    }
    printf("\n");
  }
}

vc<mint> random_poly(int n, Random &gen) {
  vc<mint> f(n + 1);
  f[n] = 1;
  FOR(i, n) f[i] = gen.uniform<int>(0, mint::get_mod() - 1);
  return f;
}

vvc<mint> gen_mat(vc<int> S, Random &gen) {
  sort(all(S));
  int B = len(S);
  vvc<mint> poly(B);
  poly[0] = random_poly(S[0], gen);
  FOR(b, 1, B) {
    vc<mint> f = poly[b - 1];
    vc<mint> g = random_poly(S[b] - S[b - 1], gen);
    vc<mint> F(S[b] + 1);
    FOR(i, len(f)) FOR(j, len(g)) F[i + j] += f[i] * g[j];
    poly[b] = F;
  }
  // desc
  reverse(all(S));
  reverse(all(poly));
  int N = 0;
  for (auto &x: S) N += x;
  int s = 0;
  vvc<mint> A(N, vc<mint>(N));
  FOR(b, B) {
    int d = S[b];
    FOR(i, d - 1) A[s + i + 1][s + i] = 1;
    FOR(i, d) A[s + i][s + d - 1] = -poly[b][i];
    s += d;
  }
  assert(s == N);
  // inv(P) A P
  while (1) {
    vvc<mint> P(N, vc<mint>(N));
    FOR(i, N) FOR(j, N) P[i][j] = gen.uniform<int>(0, mint::get_mod() - 1);
    auto [det, IP] = matrix_inv<mint>(P);
    if (det == mint(0)) continue;
    A = matrix_mul<mint>(IP, A);
    A = matrix_mul<mint>(A, P);
    return A;
  }
}

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;

  if (0 <= seed && seed < 5) {
    int ks[] = {1, 2, 5, 10, 20};
    int K = ks[seed];
    vc<int> S;
    int now = 0;
    while (now < N) {
      int k = gen.uniform<int>(1, K);
      if (now + k > N) continue;
      S.emplace_back(k), now += k;
    }
    vvc<mint> A = gen_mat(S, gen);
    out(N, A);
  }
  elif (5 <= seed && seed < 10) {
    int ks[] = {1, 2, 5, 10, 20};
    int K = ks[seed - 5];
    vc<int> cut = gen.choice(K - 1, 1, N - 1);
    cut.insert(cut.begin(), 0);
    cut.emplace_back(N);
    assert(len(cut) == K + 1);
    vc<int> S(K);
    FOR(i, K) S[i] = cut[i + 1] - cut[i];
    vvc<mint> A = gen_mat(S, gen);
    out(N, A);
  }
  else {
    assert(0);
  }
  return 0;
}
