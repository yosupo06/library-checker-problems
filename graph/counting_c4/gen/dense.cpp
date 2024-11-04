#include "../params.h"
#include "random.h"
#include <cstdio>

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = 10;
  int m = M_MAX;

  std::printf("%d %d\n", n, m);

  for(int i=0; i<m; i++){
    int u = gen.uniform(0, n-1);
    int v = gen.uniform(0, n-2);
    if(u <= v) v += 1;
    std::printf("%d %d\n", u, v);
  }
}
