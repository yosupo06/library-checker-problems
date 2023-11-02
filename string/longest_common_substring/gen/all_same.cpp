#include <cstdio>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(N_MAX - 10000, N_MAX);
  int m = gen.uniform(N_MAX - 10000, N_MAX);

  char c = gen.uniform('a', 'z');
  string s(n, c);
  string t(m, c);

  printf("%s\n", s.c_str());
  printf("%s\n", t.c_str());
  return 0;
}
