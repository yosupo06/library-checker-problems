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
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    auto a = uniform128(gen, -A_AND_B_MAX, A_AND_B_MAX);
    auto b = uniform128(gen, -A_AND_B_MAX, A_AND_B_MAX);
    string A = i128_to_str(a);
    string B = i128_to_str(b);
    printf("%s %s\n", A.c_str(), B.c_str());
  }
  return 0;
}
