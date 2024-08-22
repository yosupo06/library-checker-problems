#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int n = gen.uniform<int>(N_MAX * 0.9, N_MAX);
  vector<vector<int>> a(n, vector<int>(n));
  vector<int> p = gen.perm<int>(n);
  for (int i = 0; i < n; i++) { a[i][p[i]] = gen.uniform(0, 1); }

  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    string S(n, '0');
    for (int j = 0; j < n; j++) { S[j] = a[i][j] + '0'; }
    printf("%s\n", S.c_str());
  }
  return 0;
}
