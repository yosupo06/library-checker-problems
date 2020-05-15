#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <vector>

using i64 = long long;
constexpr i64 MOD = 998244353;

int main() {
  int n;
  std::scanf("%d", &n);
  assert(n <= 11);

  std::vector<std::vector<i64>> a(n, std::vector<i64>(n));
  for (auto &v : a) {
    for (i64 &e : v) {
      std::scanf("%lld", &e);
    }
  }

  i64 ans = 0;

  std::vector<int> idx(n);
  std::iota(idx.begin(), idx.end(), 0);
  do {
    bool f = true;
    for (int i = 0; i != n; i += 2) {
      if (idx[i] > idx[i + 1]) {
        f = false;
      }
    }
    for (int i = 2; i != n; i += 2) {
      if (idx[i - 2] > idx[i]) {
        f = false;
      }
    }
    if (!f) {
      continue;
    }

    i64 prod = 1;
    for (int i = 0; i != n; i += 2) {
      prod = (prod * a[idx[i]][idx[i + 1]]) % MOD;
    }
    ans = (ans + prod) % MOD;
  } while (std::next_permutation(idx.begin(), idx.end()));

  std::printf("%lld\n", ans);
}
