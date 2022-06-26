#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(N_MIN, N_MAX);
  int K = gen.uniform<int>(K_MIN, min<int>(K_MAX, N - 1));

  vector<int> I, A;
  for (int k = 0; k < K; k++) {
    int i, a;
    while (1) {
      i = gen.uniform<int>(1, N - 1);
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

  printf("%d %d\n", N, K);
  for (int k = 0; k < K; ++k) { printf("%d %d\n", I[k], A[k]); }
  return 0;
}
