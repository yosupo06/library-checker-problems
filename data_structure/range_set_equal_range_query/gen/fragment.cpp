#include <iostream>
#include <tuple>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long caseid = atoll(argv[1]);
  long long seed = caseid + 100;
  auto gen = Random(seed);

  int n = N_AND_Q_MAX;
  int q = N_AND_Q_MAX;

  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    int a = gen.uniform<int>(1, A_MAX);
    printf("%d", a);
  }
  printf("\n");
  for (int i = 0; i < q; i++) {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0) {
      int l = -1;
      int r = -1;
      int x = gen.uniform<int>(1, A_MAX);
      while (l == -1 || n < r) {
        l = gen.uniform(0, n);
        r = l + gen.uniform(1, 10);
      }
      printf("%d %d %d\n", l, r, x);
    } else {
      int i = gen.uniform<int>(0, n - 1);
      printf("%d\n", i);
    }
  }
  return 0;
}
