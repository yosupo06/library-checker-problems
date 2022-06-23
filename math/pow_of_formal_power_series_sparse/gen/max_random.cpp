#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int K = K_MAX;
  int M = gen.uniform<int>(M_MIN, M_MAX);

  vector<int> I, A;
  for (int k = 0; k < K; k++) {
    int i, a;
    while (1) {
      i = gen.uniform<int>(0, N - 1);
      if (k == 0) i = 0;
      a = gen.uniform<int>(1, MOD - 1);
      // 新しい i になっているか？
      bool ok = [&]() {
        for (auto&& j: I)
          if (i == j) return 0;
        return 1;
      }();
      if (ok) break;
    }
    I.push_back(i);
    A.push_back(a);
  }
  sort(I.begin(), I.end());

  printf("%d %d %d\n", N, K, M);
  for (int k = 0; k < K; ++k) { printf("%d %d\n", I[k], A[k]); }
  return 0;
}
