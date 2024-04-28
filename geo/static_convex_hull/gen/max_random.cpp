#include <cstdio>
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

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int lims[] = {X_AND_Y_ABS_MAX, 10, 1000, 100000};

  int LIM = lims[seed % 4];

  vector<vector<P>> ALL;
  int n = SUM_N_MAX;
  vector<P> S;
  for (int i = 0; i < n; ++i) S.emplace_back(random_point(gen, LIM));
  ALL.emplace_back(S);

  out(ALL);
  return 0;
}
