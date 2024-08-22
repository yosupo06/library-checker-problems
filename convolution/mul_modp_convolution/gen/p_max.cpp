#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int P = 524287;

  vector<int> a(P), b(P);
  for(int &x : a)
    x = gen.uniform(0LL, MOD - 1);
  for(int &x : b)
    x = gen.uniform(0LL, MOD - 1);

  printf("%d\n", P);
  for(int i = 0; i < P; i++)
    printf("%d%c", a[i], " \n"[i + 1 == P]);
  for(int i = 0; i < P; i++)
    printf("%d%c", b[i], " \n"[i + 1 == P]);

  return 0;
}
