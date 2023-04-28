#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

#include "../base.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;

  constexpr int MAX_DIGIT = LOG_10_A_AND_B_MAX;
  // n digits integer : [ten[n], ten[n + 1])
  // ten = {0, 1, 10, 100, ...}
  vector<i128> ten(MAX_DIGIT + 1);
  for (int d = 1; d <= MAX_DIGIT; d++) ten[d] = TEN(d);

  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int d1 = gen.uniform(0, MAX_DIGIT - 1);
    int d2 = gen.uniform(0, MAX_DIGIT - 1);
    auto a = uniform128(gen, ten[d1], ten[d1 + 1] - 1);
    auto b = uniform128(gen, ten[d2], ten[d2 + 1] - 1);
    if (gen.uniform_bool()) a = -a;
    if (gen.uniform_bool()) b = -b;
    string A = i128_to_str(a);
    string B = i128_to_str(b);
    printf("%s %s\n", A.c_str(), B.c_str());
  }
  return 0;
}
