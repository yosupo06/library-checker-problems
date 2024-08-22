#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

using ll = long long;
using u64 = unsigned long long;
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

int det_mod(vc<vc<int>> A, int mod) {
  const int n = A.size();
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
  FOR(i, n) det = det * A[i][i] % mod;
  return det % mod;
}

char BUF[5000];

void solve() {
  int N;
  scanf("%d", &N);
  assert(N <= 1000);
  vc<vc<int>> mat(N, vc<int>(N));
  FOR(i, N) {
    scanf("%s", BUF);
    FOR(j, N) mat[i][j] = (BUF[j] - '0');
  }
  int ans = det_mod(mat, 2);
  printf("%d\n", ans);
}

signed main() { solve(); }
