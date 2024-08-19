#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(N_MIN, N_MAX);
  int K = K_MIN;
  ll M = gen.uniform<ll>(M_MIN, M_MAX);

  assert(K==0);
  printf("%d %d %lld\n", N, K, M);
  return 0;
}
