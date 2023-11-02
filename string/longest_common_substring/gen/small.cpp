#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(1, 5);
  int m = gen.uniform(1, 5);
  string s, t;
  for (int i = 0; i < n; ++i) s += gen.uniform('a', 'b');
  for (int i = 0; i < m; ++i) t += gen.uniform('a', 'b');
  printf("%s\n", s.c_str());
  printf("%s\n", t.c_str());
  return 0;
}
