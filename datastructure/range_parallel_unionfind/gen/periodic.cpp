#include <cstdio>
#include <cstdlib>
#include <tuple>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(MAX_N - 10, MAX_N);
  int Q = MAX_Q;

  int ps[] = {2, 10, 100, 1000};
  int p = ps[seed % 4];

  auto get = [&](int p) -> tuple<int, int, int> {
    // (a-b) % p==0
    while (1) {
      int k = gen.uniform<int>(0, N);
      int a = gen.uniform<int>(0, N - k);
      int b = gen.uniform<int>(0, N - k);
      // b を増やして a と合同にする
      int add = (a - b) % p;
      if (add < 0) add += p;
      b += add;
      if (b <= N - k) return {k, a, b};
    }
    assert(0);
  };

  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d", x);
  }
  printf("\n");

  for (int i = 0; i < Q; i++) {
    auto [k, a, b] = get(p);
    printf("%d %d %d\n", k, a, b);
  }
  return 0;
}