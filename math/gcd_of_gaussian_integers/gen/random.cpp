#include <iostream>
#include <vector>
#include <tuple>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int T = T_MAX;
  printf("%d\n", T);
  for (int t = 0; t < T; ++t) {
    int a = gen.uniform<int>(MIN, MAX);
    int b = gen.uniform<int>(MIN, MAX);
    int c = gen.uniform<int>(MIN, MAX);
    int d = gen.uniform<int>(MIN, MAX);
    printf("%d %d %d %d\n", a, b, c, d);
  }
  return 0;
}
