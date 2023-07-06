#include <cstdio>
#include <set>

#include "../params.h"
#include "random.h"

using namespace std;

bool check(int a, int r, int N) {
  long long x = a;
  set<int> s;
  for (int i = 0; i < N; ++i) {
    s.insert(x);
    x = x * r % MOD;
  }
  return int(s.size()) == N;
}

pair<int, int> make_ar(Random &gen, int N) {
  int a, r;
  while (1) {
    a = gen.uniform<int>(0, MOD - 1);
    r = gen.uniform<int>(0, MOD - 1);
    if (check(a, r, N)) break;
  }
  return {a, r};
}

vector<int> make_y(Random &gen, int n) {
  vector<int> y(n);
  for (int i = 0; i < n; ++i) y[i] = gen.uniform<int>(0, MOD - 1);
  return y;
}

void output(int N, int a, int r, vector<int> y) {
  printf("%d %d %d\n", N, a, r);
  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", y[i]);
  }
  printf("\n");
}
