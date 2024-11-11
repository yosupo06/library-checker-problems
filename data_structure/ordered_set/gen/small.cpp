#include <iostream>
#include <string>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int K = seed % 3 + 1;
  int Q = Q_MAX;

  vector<int> A;
  for (int x = 0; x < K; ++x) {
    if (gen.uniform<int>(0, 1)) A.emplace_back(x);
  }
  int N = A.size();

  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    printf("%d", A[i]);
  }
  printf("\n");

  for (int i = 0; i < Q; i++) {
    int t = gen.uniform(0, 5);
    int x = gen.uniform(0, K - 1);
    if (t == 2) ++x;
    printf("%d %d\n", t, x);
  }
  return 0;
}
