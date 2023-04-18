#include <iostream>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int sqrtn = (int)sqrt(N_AND_Q_MAX);
  int n = sqrtn*sqrtn;
  int q = N_AND_Q_MAX;
  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++) {
        int a = gen.uniform<int>(1, MOD - 1);
        int b = gen.uniform<int>(0, MOD - 1);
        printf("%d %d\n", a, b);
    }

  vector<int> u(n - 1), v(n - 1);

  int len=2*sqrtn-1, pr=0, p=0;
  while (len>0) {
    u[p]=pr;
    v[p]=pr+len;
    ++p;
    for (int i=0;i<len-1;++i) {
      u[p]=pr+i;
      v[p]=pr+i+1;
      ++p;
    }
    pr+=len;
    len-=2;
  }

  for (int i = 0; i < n - 1; i++) {
    printf("%d %d\n", u[i], v[i]);
  }

  for (int i = 0; i < q; i++) {
    printf("1 ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d %d %d\n", 0, n-1, x);
  }
  return 0;
}
