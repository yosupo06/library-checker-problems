#include <iostream>
#include <tuple>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_AND_Q_MAX;
  int q = N_AND_Q_MAX;
  printf("%d %d\n", n, q);

  int www[] = {1, 100, 10000};
  int kkk[] = {1, 2, 10};

  int w = www[seed / 3];
  int k = kkk[seed % 3];
  vector<int> S = gen.choice<int>(k, 1, A_MAX);
  auto get_a = [&]() -> int {
    int idx = gen.uniform<int>(0, k - 1);
    return S[idx];
  };
  auto get_lr = [&]() -> pair<int, int> {
    int l = gen.uniform<int>(0, n - w);
    int r = l + w;
    return {l, r};
  };

  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    int a = get_a();
    printf("%d", a);
  }
  printf("\n");
  for (int i = 0; i < q; i++) {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0) {
      int l, r;
      tie(l, r) = get_lr();
      int x = get_a();
      printf("%d %d %d\n", l, r, x);
    } else {
      int i = gen.uniform<int>(0, n - 1);
      printf("%d\n", i);
    }
  }
  return 0;
}
