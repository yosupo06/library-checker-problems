#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int l = 10;
  int t = l * l * l;
  printf("%d\n", t);
  for (int a = 0; a < l; a++) {
    for (int b = 0; b < l; b++) {
      for (int m = 1; m <= l; m++) {
        int mod = gen.uniform(1LL, 1'000'000'000LL);
        printf("%d %d %d\n", a, b, mod);
      }
    }
  }
  return 0;
}