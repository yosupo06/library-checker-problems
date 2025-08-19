#include <vector>
#include <cstdlib>
#include <cstdio>
#include <tuple>

using namespace std;
using ll = long long;

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

int rd() {
  int x;
  scanf("%d", &x);
  return x;
}

void solve() {
  int N = rd(), Q = rd();
  vc<int> A(N);
  FOR(i, N) A[i] = rd();
  FOR(Q) {
    int t = rd();
    if (t == 0) {
      int l = rd(), r = rd(), x = rd();
      FOR(i, l, r) A[i] = x;
    }
    if (t == 1) {
      int i = rd();
      int x = A[i];
      int l = i, r = i + 1;
      while (0 < l && A[l - 1] == A[i]) --l;
      while (r < N && A[i] == A[r]) ++r;
      printf("%d %d %d\n", x, l, r);
    }
  }
}

signed main() { solve(); }
