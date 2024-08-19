#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  // 次数と M を 100 以下にする。
  int N = N_MAX;
  int K = K_MAX;
  ll M = gen.uniform<ll>(M_MIN, 100);
  
  vector<int> I, A;
  for (int k = 0; k < K; k++) {
    int i, a;
    while (1) {
      i = gen.uniform<int>(0, N - 1);
      if (k == 0) i = gen.uniform<int>(0, 100);
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

  printf("%d %d %lld\n", N, K, M);
  for (int k = 0; k < K; ++k) { printf("%d %d\n", I[k], A[k]); }
  return 0;
}
