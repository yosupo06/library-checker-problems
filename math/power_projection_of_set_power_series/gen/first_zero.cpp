#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

using namespace std;

void out(Random& gen, int N, int M) {
  printf("%d %d\n", N, M);

  for (int i = 0; i < (1 << N); ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    if (i == 0) x = 0;
    printf("%d", x);
  }
  printf("\n");

  for (int i = 0; i < (1 << N); ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d", x);
  }
  printf("\n");
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int N = gen.uniform<int>(0, N_MAX);
  const int M = gen.uniform<int>(0, M_MAX);

  out(gen, N, M);
}
