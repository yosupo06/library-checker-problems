#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

bool isPrime(int x) {
  if (x < 2) return false;
  for(int i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int P = -1;
  do {
    P = gen.uniform(1LL << (7 + seed / 2), 1LL << (8 + seed / 2));
  } while(!isPrime(P));

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
