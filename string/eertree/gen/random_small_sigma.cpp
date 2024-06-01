#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int sigma = (seed % 5) + 1;
  string s;
  for (int i = 0; i < MAX_N; ++i) { s += 'a' + gen.uniform(0, sigma - 1); }
  printf("%s\n", s.c_str());

  return 0;
}
