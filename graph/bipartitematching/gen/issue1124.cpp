#include <vector>
#include <iostream>
#include <algorithm>

#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int B = 12;
  vector<pair<int, int> > edges;
  for (int i = 0; i <= B; i++) {
    for (int j = 0; j < (1 << B); j++) {
      edges.push_back({(i << B) + j, (i << B) + j});
    }
  }
  for (int i = 0; i < B; i++) {
    for (int j = 0; j < (1 << B); j++) {
      edges.push_back({((i + 1) << B) + j, (i << B) + j});
      edges.push_back({((i + 1) << B) + (j ^ (1 << i)), (i << B) + j});
    }
  }
  for (int i = 0; i < (1 << B); i++) {
    edges.push_back({((B + 1) << B) + i, (B << B) + i});
  }
  for (int i = 0; i < (1 << B); i++) {
    edges.push_back({i, ((B + 1) << B) + i});
  }

  int l = (B + 2) << B;
  int r = (B + 2) << B;
  int m = edges.size();

  if (seed % 3 == 0) {
    // shuffle
    vector<int> new_idx_L(l), new_idx_R(r);
    for (int i = 0; i < l; ++i) new_idx_L[i] = i;
    for (int i = 0; i < r; ++i) new_idx_R[i] = i;
    gen.shuffle(edges.begin(), edges.end());
    gen.shuffle(new_idx_L.begin(), new_idx_L.end());
    gen.shuffle(new_idx_R.begin(), new_idx_R.end());
    for (auto& [a, b]: edges) a = new_idx_L[a], b = new_idx_R[b];
  }
  if (seed % 3 == 2) { reverse(edges.begin(), edges.end()); }

  printf("%d %d %d\n", l, r, m);
  for (auto edge: edges) { printf("%d %d\n", edge.first, edge.second); }
  return 0;
}