#include <cstdio>
#include "../params.h"
#include "random.h"
#include <vector>

#include "common.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = N_MAX;

  int LIM = A_MAX / n * 2;
  int lo_1 = (seed & 1 ? -LIM : 0);
  int hi_1 = (seed & 1 ? 0 : LIM);
  int lo_2 = (seed & 2 ? -LIM : 0);
  int hi_2 = (seed & 2 ? 0 : LIM);

  vector<ll> A = rand_gen(gen, n, lo_1, hi_1, A_MAX);
  vector<ll> B = rand_gen(gen, m, lo_2, hi_2, A_MAX);

  for (int i = 0; i < n - 1; ++i) {
    if (!(seed & 1)) assert(A[i] <= A[i + 1]);
    if (seed & 1) assert(A[i] >= A[i + 1]);
  }
  for (int i = 0; i < m - 1; ++i) {
    if (!(seed & 2)) assert(B[i] <= B[i + 1]);
    if (seed & 2) assert(B[i] >= B[i + 1]);
  }

  out(A, B);

  return 0;
}
