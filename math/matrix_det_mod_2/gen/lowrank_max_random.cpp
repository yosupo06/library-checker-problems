#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

const int Mod = 2;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(N_MAX * 0.9, N_MAX);
  int rank = gen.uniform<int>(1, n - 1);

  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < rank; i++) {
    a[i][i] = gen.uniform(1, Mod - 1);
    for (int j = i + 1; j < n; j++) { a[i][j] = gen.uniform(0, Mod - 1); }
  }
  for (int ph = 0; ph < 50000; ph++) {
    int x = gen.uniform(0, n - 1);
    int y = gen.uniform(0, n - 1);
    int freq = gen.uniform(1, Mod - 1);
    if (x == y) continue;
    if (gen.uniform_bool()) {
      for (int i = 0; i < n; i++) {
        a[x][i] += freq * a[y][i];
        a[x][i] %= Mod;
      }
    } else {
      for (int i = 0; i < n; i++) {
        a[i][x] += freq * a[i][y];
        a[i][x] %= Mod;
      }
    }
  }

  gen.shuffle(a.begin(), a.end());
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) { swap(a[i][j], a[j][i]); }
  }
  gen.shuffle(a.begin(), a.end());

  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    string S(n, '0');
    for (int j = 0; j < n; j++) { S[j] = a[i][j] + '0'; }
    printf("%s\n", S.c_str());
  }
  return 0;
}
