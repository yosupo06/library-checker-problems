#include <iostream>
#include <tuple>
#include "random.h"

#include "common.hpp"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<int> ns = {0, 0, 0, 0, 1, 1, 1, 1};
  vector<int> as = {0, 0, -1, -1, 0, 0, -1, -1};
  vector<int> rs = {0, -1, 0, -1, 0, -1, 0, -1};

  int N = ns[seed % 8];
  int a = as[seed % 8];
  int r = rs[seed % 8];
  if (a == -1) a = gen.uniform<int>(0, MOD - 1);
  if (r == -1) r = gen.uniform<int>(0, MOD - 1);

  vector<int> y = make_y(gen, N);
  output(N, a, r, y);

  return 0;
}
