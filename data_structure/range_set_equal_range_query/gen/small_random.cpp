#include "random.h"
#include <iostream>
#include <tuple>
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 2000);
  int q = gen.uniform<int>(1, 2000);
  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    int a = gen.uniform<int>(1, 100);
    printf("%d", a);
  }
  printf("\n");
  for (int i = 0; i < q; i++) {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0) {
      int l, r;
      tie(l, r) = gen.uniform_pair(0, n);
      int x = gen.uniform<int>(1, A_MAX);
      printf("%d %d %d\n", l, r, x);
    } else {
      int i = gen.uniform<int>(0, n - 1);
      printf("%d\n", i);
    }
  }
  return 0;
}
