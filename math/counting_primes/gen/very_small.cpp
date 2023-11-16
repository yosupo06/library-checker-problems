#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  ll N = seed % 5 + 1;
  printf("%lld\n", N);
  return 0;
}