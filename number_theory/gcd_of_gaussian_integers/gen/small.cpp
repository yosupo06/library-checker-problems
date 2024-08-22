#include <iostream>
#include <vector>
#include <tuple>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  // auto gen = Random(seed); つかわない

  const int LIM = 10;
  vector<tuple<int, int, int, int>> problems;
  for (int a = -LIM; a <= LIM; ++a) {
    for (int b = -LIM; b <= LIM; ++b) {
      for (int c = -LIM; c <= LIM; ++c) {
        for (int d = -LIM; d <= LIM; ++d) {
          if ((a + b + c + d + seed) % 2 == 0)
            problems.emplace_back(a, b, c, d);
        }
      }
    }
  }

  int t = problems.size();
  assert(1 <= t && t <= T_MAX);
  printf("%d\n", t);
  for (auto& [a, b, c, d]: problems) { printf("%d %d %d %d\n", a, b, c, d); }
  return 0;
}
