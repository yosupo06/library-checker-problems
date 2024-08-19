#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  int n, q;
  std::scanf("%d%d", &n, &q);

  if ((long long)q * n * n > 10000000) {
    std::abort();
  }

  std::vector<int> a(n);
  for (auto &e : a) {
    std::scanf("%d", &e);
  }

  for (int i = 0; i != q; ++i) {
    int l, r;
    std::scanf("%d%d", &l, &r);
    long long ans = 0;
    for (int j = l; j != r; ++j) {
      for (int k = l; k != j; ++k) {
        if (a[k] > a[j]) {
          ++ans;
        }
      }
    }
    std::printf("%lld\n", ans);
  }

  return 0;
}
