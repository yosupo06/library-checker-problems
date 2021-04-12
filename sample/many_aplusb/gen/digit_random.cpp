#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

constexpr int MAX_DIGIT = 18;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  long long ten[MAX_DIGIT + 1];
  ten[0] = 1;
  for (int i = 1; i <= MAX_DIGIT; i++) ten[i] = ten[i - 1] * 10;
  ten[0] = 0;

  int t = T_MAX;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int d = gen.uniform(1, MAX_DIGIT);
    auto a = gen.uniform(ten[d - 1], ten[d] - 1);
    auto b = gen.uniform(ten[d - 1], ten[d] - 1);
    printf("%lld %lld\n", a, b);
  }
  return 0;
}
