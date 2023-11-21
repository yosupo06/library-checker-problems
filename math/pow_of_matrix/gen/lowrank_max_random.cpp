#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;

void out(int n, ll K, vector<vector<ll>> a) {
  printf("%d %lld\n", n, K);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%lld", a[i][j]);
      if (j + 1 != n) printf(" ");
    }
    printf("\n");
  }
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(N_MAX - 10, N_MAX);
  int rank = gen.uniform(1, n - 1);

  vector<vector<ll>> a(n, vector<ll>(n));
  for (int i = 0; i < rank; i++) {
    a[i][i] = gen.uniform(1LL, MOD - 1);
    for (int j = i + 1; j < n; j++) { a[i][j] = gen.uniform(0LL, MOD - 1); }
  }
  for (int ph = 0; ph < 10000; ph++) {
    int x = gen.uniform(0, n - 1);
    int y = gen.uniform(0, n - 1);
    ll freq = gen.uniform(1LL, MOD - 1);
    if (x == y) continue;
    if (gen.uniform_bool()) {
      for (int i = 0; i < n; i++) {
        a[x][i] += freq * a[y][i];
        a[x][i] %= MOD;
      }
    } else {
      for (int i = 0; i < n; i++) {
        a[i][x] += freq * a[i][y];
        a[i][x] %= MOD;
      }
    }
  }

  gen.shuffle(a.begin(), a.end());
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) { swap(a[i][j], a[j][i]); }
  }
  gen.shuffle(a.begin(), a.end());

  ll K = gen.uniform<ll>(0, K_MAX);
  out(n, K, a);
  return 0;
}
