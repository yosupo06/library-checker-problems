#include <iostream>
#include <cinttypes>
#include "random.h"
#include "../params.h"
#include "../lib/prime.hpp"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  PrimeGenerator pgen;

  auto F = [&]() -> ll {
    while (1) {
      ll p = pgen.gen(MAX_A, gen);
      if (p % 4 == 3) return p;
    }
  };

  int Q = MAX_Q;
  printf("%d\n", Q);
  for (int i = 0; i < Q; i++) { printf("%lld\n", F()); }
}
