#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int k = seed % 4;
  int n = gen.uniform<int>(k + 1, N_MAX);
  // ll q = M_MAX;
  ll q_max = M_MAX;
  if (k != 0) q_max = (n - 1) / k;
  ll q = gen.uniform<ll>(0, q_max);
  printf("%d %lld\n", n, q);
  for (int i = 0; i < n; i++) {
    int x = (i == k ? gen.uniform<int>(1, MOD - 1) : 0);
    printf("%d", x);
    if (i != n - 1) printf(" ");
  }
  printf("\n");
  return 0;
}
