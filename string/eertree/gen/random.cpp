#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  string s;
  for (int i = 0; i < MAX_N; ++i) { s += char(gen.uniform('a', 'z')); }
  printf("%s\n", s.c_str());

  return 0;
}
