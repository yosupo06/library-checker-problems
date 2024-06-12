#include <cstdio>
#include <cstdlib>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(MAX_N - 10, MAX_N);
  int Q = MAX_Q;
  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d", x);
  }
  printf("\n");

  for (int i = 0; i < Q; i++) {
    int k = gen.uniform<int>(0, 100);
    int a = gen.uniform<int>(0, N - k);
    int b = gen.uniform<int>(0, N - k);
    printf("%d %d %d\n", k, a, b);
  }
  return 0;
}