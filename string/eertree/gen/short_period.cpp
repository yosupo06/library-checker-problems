#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  vector<string> fixed_period_list
      = {string("a"), string("z"), string("ab"), string("zyz"), string("abc")};

  string period = fixed_period_list.at(seed / 2);
  int maxlen = MAX_N;
  if (seed % 2 == 1) maxlen /= 2;
  string s;
  while (int(s.size() + period.size()) <= maxlen) { s += period; }
  printf("%s\n", s.c_str());
  return 0;
}
