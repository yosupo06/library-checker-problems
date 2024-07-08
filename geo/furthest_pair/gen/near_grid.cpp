#include <cstdio>
#include <cstdlib>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

P random_point(Random& gen, int LIM) {
  int x = gen.uniform(-LIM, LIM);
  int y = gen.uniform(-LIM, LIM);
  return {x, y};
}

void out(vector<vector<P>> ALL) {
  int T = ALL.size();
  printf("%d\n", T);
  for (auto& S: ALL) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%d %d\n", x, y); }
  }
}

/*
This code is not implemented as intended.
The correct implementation can be found in fix_near_grid.cpp.
https://github.com/yosupo06/library-checker-problems/issues/1204
*/
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<vector<P>> ALL;
  int n = 1;
  while ((n + 1) * (n + 1) <= SUM_N_MAX) ++n;
  int N = n * n;

  int eps = 100;
  /*
  x[0],x[1],...,x[N-1]
  */
  int LIM = X_AND_Y_ABS_MAX;
  int d = LIM / (N - 1); // this line should be int d = LIM / (n - 1);

  auto get = [&](int i) -> int {
    int x = i * d - (LIM / 2);
    return x + gen.uniform<int>(-eps, eps);
  };

  vector<P> S;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x = get(i), y = get(j);
      S.emplace_back(x, y);
    }
  }
  ALL.emplace_back(S);

  out(ALL);
  return 0;
}
