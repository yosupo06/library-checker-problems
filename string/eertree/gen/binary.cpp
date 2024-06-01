#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int maxlen = MAX_N;
  string s;
  for (int d = 0; int(s.size() * 2 + 1) < maxlen; d++) {
    string t = s + string(1, 'a' + d) + s;
    s = t;
  }

  while (int(s.size()) < MAX_N) { s += 'a' + (gen.uniform<int>(0, 1)); }
  printf("%s\n", s.c_str());

  return 0;
}
