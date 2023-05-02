#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
  using ll = long long;
  int N, Q;
  scanf("%d%d", &N, &Q);
  std::vector<int> a(N);
  for (auto &e : a)
    scanf("%d", &e);
  for (int j = 0; j < Q; j++) {
    int t, l, r;
    scanf("%d%d%d", &t, &l, &r);
    if (t == 0)
      std::reverse(a.begin() + l, a.begin() + r);
    else
      printf("%lld\n", std::accumulate(a.begin() + l, a.begin() + r, ll(0)));
  }
}
