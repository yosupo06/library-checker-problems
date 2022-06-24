#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int K = gen.uniform<int>(K_MIN, K_MAX);

  vector<int> I, A;
  for (int k = 1; k < K + 1; k++) {
    int i, a;
    i = k;
    a = gen.uniform<int>(1, MOD - 1);
    I.push_back(i);
    A.push_back(a);
  }
  sort(I.begin(), I.end());

  printf("%d %d\n", N, K);
  for (int k = 0; k < K; ++k) { printf("%d %d\n", I[k], A[k]); }
  return 0;
}
