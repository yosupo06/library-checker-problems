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

using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = SUM_N_MAX;
  vector<P> vect;
  for (ll x = 2; x <= n; ++x) {
    if (int(vect.size()) == n - 1) break;
    for (ll y = 1; y <= x; ++y) {
      if (gcd(x, y) > 1) continue;
      if (int(vect.size()) == n - 1) break;
      vect.emplace_back(x, y);
    }
  }

  sort(vect.begin(), vect.end(), [&](auto& a, auto& b) -> bool {
    return ll(a.second) * b.first < ll(a.first) * b.second;
  });

  vector<P> S;
  S.emplace_back(0, 0);
  int x = 0, y = 0;
  for (auto& [a, b]: vect) {
    x += a, y += b;
    S.emplace_back(x, y);
  }

  gen.shuffle(S.begin(), S.end());

  vector<vector<P>> ALL;
  ALL.emplace_back(S);

  out(ALL);
  return 0;
}
