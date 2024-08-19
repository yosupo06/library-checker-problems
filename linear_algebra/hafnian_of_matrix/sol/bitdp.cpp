#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <vector>

using i64 = long long;
constexpr i64 MOD = 998244353;

bool parity(int x) {
  bool ret = false;
  while (x != 0) {
    if (x % 2 != 0) {
      ret ^= 1;
    }
    x /= 2;
  }
  return ret;
}

int main() {
  int n;
  std::scanf("%d", &n);
  assert(n <= 25);

  std::vector<std::vector<i64>> a(n, std::vector<i64>(n));
  for (auto &v : a) {
    for (i64 &e : v) {
      std::scanf("%lld", &e);
    }
  }

  std::vector<i64> dp(1 << n, 0);
  dp[0] = 1;

  for (int i = 1; i != 1 << n; ++i) {
    if (parity(i)) {
      continue;
    }
    int j = 0;
    while ((i >> j & 1) == 0) {
      j += 1;
    }
    for (int k = j + 1; k != n; ++k) {
      if ((i >> k & 1) == 0) {
        continue;
      }
      dp[i] = (dp[i] + a[j][k] * dp[i ^ 1 << j ^ 1 << k]) % MOD;
    }
  }

  std::printf("%lld\n", dp.back());
}
