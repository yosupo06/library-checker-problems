#include <iostream>

#include "random.h"

using namespace std;

using ll = long long;
const ll Mod = 998244353;

vector<vector<ll>> gen_matrix(int n, int m, int r, Random& gen) {
  vector<vector<ll>> a(n, vector<ll>(m));
  for (int i = 0; i < r; i++) {
    a[i][i] = gen.uniform(1LL, Mod - 1);
    for (int j = i + 1; j < m; j++) { a[i][j] = gen.uniform(0LL, Mod - 1); }
  }
  for (int ph = 0; ph < 10000; ph++) {
    if (gen.uniform_bool()) {
      // column add
      int x = gen.uniform(0, n - 1);
      int y = gen.uniform(0, n - 1);
      ll freq = gen.uniform(1LL, Mod - 1);
      if (x == y) continue;
      for (int i = 0; i < m; i++) {
        a[x][i] += freq * a[y][i];
        a[x][i] %= Mod;
      }
    } else {
      // row add
      int x = gen.uniform(0, m - 1);
      int y = gen.uniform(0, m - 1);
      ll freq = gen.uniform(1LL, Mod - 1);
      if (x == y) continue;
      for (int i = 0; i < n; i++) {
        a[i][x] += freq * a[i][y];
        a[i][x] %= Mod;
      }
    }
  }

  // column shuffle
  gen.shuffle(a.begin(), a.end());
  // row shuffle
  for (int i = 0; i < m; i++) {
    int j = gen.uniform(0, i);
    for (int k = 0; k < n; k++) { swap(a[k][j], a[k][i]); }
  }

  return a;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = 0, m = 0;
  do {
    n = gen.uniform(1, 500);
    m = gen.uniform(1, 500);
  } while (n * 2.5 > m);

  vector<vector<ll>> a(n, vector<ll>(m));

  if (gen.uniform(0, 1) == 1) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) { a[i][j] = gen.uniform<ll>(0, Mod - 1); }
    }
  } else {
    int rank = gen.uniform(1, min(n, m));
    a = gen_matrix(n, m, rank, gen);
  }

  for (int j = 0; j < m; j++) {
    if (gen.uniform(0, 1) == 1) {
      for (int i = 0; i < n; i++) { a[i][j] = 0; }
    }
  }

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", (int)a[i][j]);
      if (j + 1 != m) printf(" ");
    }
    printf("\n");
  }

  return 0;
}
