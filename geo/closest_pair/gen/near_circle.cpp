#include <cstdio>
#include <utility>
#include "random.h"
#include "../params.h"

using namespace std;

using P = pair<int, int>;

P random_point(Random& gen) {
  long long R = X_AND_Y_ABS_MAX;
  long long x = gen.uniform(-R, R);
  long long ok = 0, ng = R + 1;
  while (ok + 1 < ng) {
    long long mi = (ok + ng) / 2;
    (x * x + mi * mi <= R * R ? ok : ng) = mi;
  }
  long long y = ok;
  if (gen.uniform<int>(0, 1)) y = -y;
  if (gen.uniform<int>(0, 1)) swap(x, y);
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
  int n = SUM_N_MAX;
  vector<P> S;
  for (int i = 0; i < n; ++i) S.emplace_back(random_point(gen));
  ALL.emplace_back(S);

  out(ALL);
  return 0;
}
