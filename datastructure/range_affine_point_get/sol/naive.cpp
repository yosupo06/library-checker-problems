#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;

const ll MOD = 998244353;

int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  assert(ll(n) * q <= TEN(8));

  vector<ll> a(n);
  for (int i = 0; i < n; i++) { scanf("%lld", &a[i]); }

  for (int ph = 0; ph < q; ph++) {
    int ty;
    scanf("%d", &ty);
    if (ty == 0) {
      int l, r;
      ll c, d;
      scanf("%d %d %lld %lld", &l, &r, &c, &d);
      for (int i = l; i < r; i++) { a[i] = (c * a[i] + d) % MOD; }
    } else {
      int idx;
      scanf("%d", &idx);
      ll sum = a[idx];
      printf("%lld\n", sum);
    }
  }
  return 0;
}
