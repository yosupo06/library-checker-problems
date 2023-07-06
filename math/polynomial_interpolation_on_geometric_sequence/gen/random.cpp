#include <iostream>
#include "random.h"

#include "common.hpp"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(1, MAX_N);
  int a, r;
  tie(a, r) = make_ar(gen, N);
  vector<int> y = make_y(gen, N);
  output(N, a, r, y);

  return 0;
}
