#include "random.h"
#include <cstdio>

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = 500'000;
  int Q = 500'000;
  printf("%d %d\n", N, Q);

  int W = 50'001;

  std::vector<int> A(N);
  int x0 = gen.uniform(0, 1'000'000'000);

  int x1 = gen.uniform(0, 1'000'000'000);
  while (x1 == x0) {
    x1 = gen.uniform(0, 1'000'000'000);
  }

  int x2 = gen.uniform(0, 1'000'000'000);
  while (x2 == x0 || x2 == x1) {
    x2 = gen.uniform(0, 1'000'000'000);
  }

  int a = (W + 1) / 2;
  int b = (W - a) / 2;
  int c = W - a - b;
  for (int i = 0; i < a; ++i) {
    A[i] = x0;
  }
  for (int i = a; i < a + b; ++i) {
    A[i] = x1;
  }
  for (int i = a + b; i < a + b + c; ++i) {
    A[i] = x2;
  }

  gen.shuffle(A.begin(), A.begin() + W);
  for (int i = W; i < N; ++i) {
    A[i] = A[i - W];
  }

  for (int i = 0; i < N; ++i) {
    if (i) {
      printf(" ");
    }
    printf("%d", A[i]);
  }
  printf("\n");

  int q = N - W + 1;
  for (int i = 0; i < q; ++i) {
    printf("1 %d %d\n", i, i + W);
  }
  for (int i = 0; i < Q - q; ++i) {
    auto [l, r] = gen.uniform_pair(0, N);
    printf("1 %d %d\n", l, r);
  }

  return 0;
}