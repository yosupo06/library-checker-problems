#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  int P = vector{2, 3, 5, 7}[seed];

  vector<int> a(P, 0), b(P, 0);

  printf("%d\n", P);
  for(int i = 0; i < P; i++)
    printf("%d%c", a[i], " \n"[i + 1 == P]);
  for(int i = 0; i < P; i++)
    printf("%d%c", b[i], " \n"[i + 1 == P]);

  return 0;
}
