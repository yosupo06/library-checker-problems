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

  // K_MIN = 0 なので次で終わり
  printf("%d %d\n", N, K);
  return 0;
}
