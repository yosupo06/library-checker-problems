#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int KIND[] = {2, 3, 10, 26};

  int n = gen.uniform(N_MAX - 100, N_MAX);
  int m = gen.uniform(N_MAX - 100, N_MAX);
  int K = KIND[seed % 4];

  string s, t;
  for (int i = 0; i < n; ++i) { s += 'a' + gen.uniform(0, K - 1); }
  for (int i = 0; i < m; ++i) { t += 'a' + gen.uniform(0, K - 1); }

  int L = gen.uniform<int>(min(n, m) / 2, min(n, m));
  int p = gen.uniform<int>(0, n - L);
  int q = gen.uniform<int>(0, m - L);
  for (int i = 0; i < L; ++i) {
    char ch = 'a' + gen.uniform(0, K - 1);
    s[p + i] = t[q + i] = ch;
  }

  printf("%s\n", s.c_str());
  printf("%s\n", t.c_str());
  return 0;
}
