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

  vector<int> ns = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};
  vector<int> ks = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};

  int n = ns[seed % 12];
  int k = ks[seed % 12];

  vector<vector<ll>> a(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { a[i][j] = gen.uniform<int>(0, MOD - 1); }
  }

  out(n, k, a);
  return 0;
}
