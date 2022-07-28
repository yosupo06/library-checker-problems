
#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 64);
  int m = gen.uniform<int>(1, 64);

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    printf("%d", gen.uniform<int>((i == n - 1), MOD - 1));
    if (i != n - 1) printf(" ");
  }
  printf("\n");
  for (int i = 0; i < m; i++) {
    printf("%d", gen.uniform<int>((i == m - 1), MOD - 1));
    if (i != m - 1) printf(" ");
  }
  printf("\n");

  return 0;
}
