#include <cstdio>
#include <vector>
#include "../acl.h"

using namespace std;
using namespace atcoder;

using mint998 = modint998244353;

int main() {
  int P;
  scanf("%d", &P);
  assert(P < (1 << 14));

  vector<mint998> a(P), b(P);
  for(int i = 0; i < P; i++) {
    int ai;
    scanf("%d", &ai);
    a[i] = ai;
  }
  for(int i = 0; i < P; i++) {
    int bi;
    scanf("%d", &bi);
    b[i] = bi;
  }

  vector<mint998> c(P);
  for(int i = 0; i < P; i++)
    for(int j = 0; j < P; j++)
      c[(long long)i * j % P] += a[i] * b[j];

  for(int i = 0; i < P; i++)
    printf("%d%c", c[i].val(), " \n"[i + 1 == P]);

  return 0;
}
