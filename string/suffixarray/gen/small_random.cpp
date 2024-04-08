#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int sz[] = {25, 26, 27, 28, 50, 51, 52, 53, 10, 100};
  int n = sz[seed % 10];
  string s = gen.lower_string(n);

  printf("%s\n", s.c_str());
  return 0;
}
