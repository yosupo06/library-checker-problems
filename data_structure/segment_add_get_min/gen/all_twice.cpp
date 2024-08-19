#include <stdio.h>
#include <algorithm>
#include <vector>
#include "../params.h"
#include "random.h"

using Int = long long;
using std::vector;

int main(int, char **argv) {
  auto rng = Random(atoll(argv[1]));

  const int N = N_AND_Q_MAX;
  const int Q = N_AND_Q_MAX;
  vector<Int> xs(2 * N + 1);
  for (int i = 0; i <= 2 * N; ++i) {
    xs[i] = rng.uniform(-A_ABS_MAX, +A_ABS_MAX - 2 * N);
  }
  std::sort(xs.begin(), xs.end());
  for (int i = 0; i <= 2 * N; ++i) {
    xs[i] += i;
  }
  auto ys = xs;
  rng.shuffle(ys.begin(), ys.end());
  ys[0] = xs[0] - 1;
  ys[1] = xs[2 * N];

  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; ++i) {
    printf("%lld %lld %lld %lld\n", xs[i], xs[N + 1 + i], (Int)i, -i * xs[N]);
  }
  for (int q = 0; q < Q; ++q) {
    printf("1 %lld\n", ys[q]);
  }
  return 0;
}
