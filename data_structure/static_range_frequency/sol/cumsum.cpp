#include <cstdio>
#include <map>
#include <utility>
#include <vector>

int main() {
  int N, Q;
  std::scanf("%d%d", &N, &Q);

  std::vector<int> a(N);
  for (int &e : a) {
    std::scanf("%d", &e);
  }

  std::vector<int> ans(Q, 0);
  std::vector<std::vector<std::pair<int, int>>> ls(N + 1), rs(N + 1);
  for (int i = 0; i < Q; i++) {
    int l, r, x;
    std::scanf("%d%d%d", &l, &r, &x);
    ls[l].push_back({x, i});
    rs[r].push_back({x, i});
  }

  std::map<int, int> map;
  for (int i = 0; i <= N; i++) {
    for (const auto &[x, j] : ls[i]) {
      ans[j] -= map[x];
    }
    for (const auto &[x, j] : rs[i]) {
      ans[j] += map[x];
    }
    if (i != N) {
      map[a[i]] += 1;
    }
  }

  for (const int &e : ans) {
    std::printf("%d\n", e);
  }

  return 0;
}
