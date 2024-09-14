#include <cassert>
#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  long long n_max = (T_sqrtN_MAX * T_sqrtN_MAX) / (T_MAX * T_MAX);
  assert(n_max <= T_MAX);
  
  printf("%lld\n", n_max);
  for (int n = 1; n <= n_max; n++) {
    int a = gen.uniform<int>(2, MOD - 1);
    int b = gen.uniform<int>(2, MOD - 1);
    printf("%d %d %d\n", n, a, b);
  }
}
