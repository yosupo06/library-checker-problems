#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  
  int l = L_MAX;
  int r = R_MAX;
  int m = M_MAX;
  int deg=1;
  while (2*deg+1<=m) {
    deg=2*deg+1;
  }
  using P = pair<int, int>;
  set<P> edges;
  for (int i=0;i<deg;++i) {
    edges.insert({0,i});
  }
  for (int ph = 0; ph < m-deg; ph++) {
    int u = gen.uniform(1, l - 1);
    int v = gen.uniform(0, r - 1);
    edges.insert({u, v});
  }
  m = int(edges.size());
  
  printf("%d %d %d\n", l, r, m);
  for (auto edge: edges) {
    printf("%d %d\n", edge.first, edge.second);
  }
  return 0;
}
