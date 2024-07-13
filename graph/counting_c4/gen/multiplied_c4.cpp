#include "../params.h"
#include "random.h"
#include <algorithm>
#include <cstdio>
#include <utility>

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = M_MAX;

  // seed 0 : divide equally
  // seed 1 : divide randomly

  auto sp = gen.choice(3, 1, m-1);
  if(seed == 0){
    sp[0] = m / 4;
    sp[1] = m * 2 / 4;
    sp[2] = m * 3 / 4;
  }
  auto nodes = gen.choice(4, 0, n-1);

  std::vector<std::pair<int, int>> edges;
  for(int i=0;     i<sp[0]; i++) edges.push_back({ nodes[0], nodes[1] });
  for(int i=sp[0]; i<sp[1]; i++) edges.push_back({ nodes[1], nodes[2] });
  for(int i=sp[1]; i<sp[2]; i++) edges.push_back({ nodes[2], nodes[3] });
  for(int i=sp[2]; i<m;     i++) edges.push_back({ nodes[3], nodes[0] });

  for (auto &e : edges) {
    if (gen.uniform_bool()) {
      std::swap(e.first, e.second);
    }
  }
  gen.shuffle(edges.begin(), edges.end());

  std::printf("%d %d\n", n, m);
  for (const auto &e : edges) {
    std::printf("%d %d\n", e.first, e.second);
  }
}
