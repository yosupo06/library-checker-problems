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
    // many carry-up
    i128 a, b;
    if (gen.uniform_bool()) {
      i128 apb = TEN(37);
      int d1 = gen.uniform(1, MAX_DIGIT - 1);
      a = uniform128(gen, ten[d1], ten[d1 + 1] - 1);
      b = apb - a;
      if (gen.uniform_bool()) a = -a, b = -b, apb = -apb;
    } else {
      a = ten[MAX_DIGIT] - gen.uniform(1, 10000);
      b = ten[MAX_DIGIT] - gen.uniform(1, 10000);
      if (gen.uniform_bool()) a = -a, b = -b;
    }
    string A = i128_to_str(a);
    string B = i128_to_str(b);
    printf("%s %s\n", A.c_str(), B.c_str());
  }
  return 0;
}
