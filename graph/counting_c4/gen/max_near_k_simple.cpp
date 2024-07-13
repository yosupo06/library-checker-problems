#include "../params.h"
#include "random.h"
#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

std::vector<int> generate_phase(int n, int k){
  std::vector<int> nph;
  for(int t=0; t<k; t++) nph.push_back((n+t)/k);
  return nph;
}

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int m = int(M_MAX);
  int k = seed + 2;

  int n = 1;
  while(true){
    n++;
    auto nph = generate_phase(n, k);
    int nxm = 0;
    for(int t=0; t<k; t++) for(int s=0; s<t; s++){
      nxm += nph[t] * nph[s];
    }
    if(nxm >= m) break;
  }

  auto nph = generate_phase(n, k);
  std::vector<int> beg_phase(k+1);
  for(int t=0; t<k; t++) beg_phase[t+1] = beg_phase[t] + nph[t];

  std::vector<std::pair<int, int>> edges;
  for(int t=0; t<k; t++) for(int s=0; s<t; s++){
    for(int p=0; p<nph[t]; p++) for(int q=0; q<nph[s]; q++){
      int a = beg_phase[t] + p;
      int b = beg_phase[s] + q;
      edges.push_back({ a, b });
    }
  }

  gen.shuffle(edges.begin(), edges.end());
  edges.resize(m);

  for (auto &e : edges) {
    if (gen.uniform_bool()) {
      std::swap(e.first, e.second);
    }
  }

  std::printf("%d %d\n", n, m);
  for (const auto &e : edges) {
    std::printf("%d %d\n", e.first, e.second);
  }
}
