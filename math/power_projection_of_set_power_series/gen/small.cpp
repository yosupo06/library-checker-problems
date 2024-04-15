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

  int ns[] = {0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2};
  int ms[] = {0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 3, 4};

  int N = ns[seed % 12];
  int M = ms[seed % 12];
  out(gen, N, M);
}
