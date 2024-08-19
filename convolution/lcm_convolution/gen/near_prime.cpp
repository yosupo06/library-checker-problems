#include "../params.h"
#include <cstdio>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int p = 999'983;
  int n = p - 1 + (seed % 3);
  vector<int> a(n), b(n);

  for (int i = 0; i < n; i++) { a[i] = gen.uniform(0ll, MOD - 1); }
  for (int i = 0; i < n; i++) { b[i] = gen.uniform(0ll, MOD - 1); }

  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", a[i]);
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", b[i]);
  }
  printf("\n");
  return 0;
}
