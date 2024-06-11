#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(N_M_MAX - 100, N_M_MAX);
  int m = n;

  printf("%d %d\n", n, m);

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    if (seed % 3 == 0) { a[i] = i - n / 2, b[i] = i + n / 2; }
    if (seed % 3 == 1) { a[i] = i / 2, b[i] = (n + i) / 2; }
    if (seed % 3 == 2) { a[i] = 0, b[i] = m; }
    if (seed % 2 == 1) {
      a[i] += gen.uniform<int>(-100, 100);
      b[i] += gen.uniform<int>(-100, 100);
    }
    a[i] = max(a[i], 0), b[i] = min(b[i], m);
  }

  for (int i = 0; i < n; i++) {
    printf("%d", a[i]);
    if (i == n - 1) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d", b[i]);
    if (i == n - 1) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  return 0;
}