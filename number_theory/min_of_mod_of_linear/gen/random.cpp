#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int n = gen.uniform<int>(NM_MIN, NM_MAX);
    int m = gen.uniform<int>(NM_MIN, NM_MAX);
    int a = gen.uniform<int>(0, m - 1);
    int b = gen.uniform<int>(0, m - 1);

    printf("%d %d %d %d\n", n, m, a, b);
  }
  return 0;
}
