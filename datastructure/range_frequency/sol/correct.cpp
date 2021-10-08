#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

int main() {
  int N, Q;
  std::scanf("%d%d", &N, &Q);

  std::map<int, std::vector<int>> map;
  for (int i = 0; i < N; i++) {
    int a;
    std::scanf("%d", &a);
    map[a].push_back(i);
  }

  for (int i = 0; i < Q; i++) {
    int l, r, x;
    std::scanf("%d%d%d", &l, &r, &x);
    const std::vector<int> &v = map[x];
    const int ans = std::lower_bound(v.begin(), v.end(), r) -
                    std::lower_bound(v.begin(), v.end(), l);
    std::printf("%d\n", ans);
  }

  return 0;
}
