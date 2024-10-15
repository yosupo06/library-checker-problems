#include <iostream>
#include <queue>
#include "../params.h"
#include "random.h"

using namespace std;

// vertex add path sum からもってきたもの
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int q = Q_MAX;
  printf("%d %d\n", n, q);

  // parent の列が必要
  vector<int> par(n, -1);
  for (int i = 0; i < n - (n / 2); i++) {
    // u[i] = i;
    // v[i] = i + 1;
    par[i + 1] = i;
  }
  for (int i = n - (n / 2); i < n - 1; i++) {
    // u[i] = gen.uniform(0, i);
    // v[i] = i + 1;
    par[i + 1] = gen.uniform(0, i);
  }
  // 頂点ラベルをシャッフルしたいが, p[i]<i にする必要がある
  // ランダム優先順位でトポロジカル順序をとる
  priority_queue<pair<int, int>> que;
  auto add_que = [&](int v) -> void {
    int pri = gen.uniform<int>(0, 1'000'000'000);
    que.emplace(pri, v);
  };
  add_que(0);

  vector<vector<int>> ch(n);
  for (int i = 1; i < n; ++i) ch[par[i]].emplace_back(i);

  vector<int> new_idx(n);
  for (int i = 0; i < n; ++i) {
    int v = que.top().second;
    que.pop();
    new_idx[v] = i;
    for (auto& w: ch[v]) add_que(w);
  }

  vector<int> tmp(n, -1);
  for (int i = 1; i < n; ++i) { tmp[new_idx[i]] = new_idx[par[i]]; }
  swap(par, tmp);

  for (int i = 1; i < n; ++i) {
    if (i > 1) printf(" ");
    printf("%d", par[i]);
  }
  printf("\n");

  for (int i = 0; i < q; i++) {
    auto [u, v] = gen.uniform_pair<int>(0, n - 1);
    printf("%d %d\n", u, v);
  }
  return 0;
}
