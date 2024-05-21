#include <cstdio>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

P random_point(Random& gen) {
  int x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
  int y = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
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

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<vector<P>> ALL;
  int now = 0;

  while (1) {
    int n = gen.uniform<int>(1, 10000);
    if (now + n > SUM_N_MAX) { break; }
    now += n;
    vector<P> S;
    auto [x, y] = random_point(gen);
    for (int i = 0; i < n; ++i) S.emplace_back(x, y);
    ALL.emplace_back(S);
  }

  out(ALL);
  return 0;
}
