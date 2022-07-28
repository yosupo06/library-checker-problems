#include <cstdio>

#include "../fastio.h"
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(1, 10000);
  int m = gen.uniform(1, 10000);
  vector<int> a(n), b(m);

  wtn(n, ' ', m);
  wtv(a);
  wtv(b);
  return 0;
}
