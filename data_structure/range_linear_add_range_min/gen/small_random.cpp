#include "random.h"
#include <iostream>
#include <tuple>
#include "../params.h"

using namespace std;

int main(int, char *argv[])
{
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 2000);
  int q = gen.uniform<int>(1, 2000);
  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++)
  {
    int a = gen.uniform<int>(-A_MAX, A_MAX);
    printf("%d", a);
    if (i != n - 1)
      printf(" ");
  }
  printf("\n");
  for (int i = 0; i < q; i++)
  {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0)
    {
      int l, r;
      tie(l, r) = gen.uniform_pair(0, n);
      int b = gen.uniform<int>(-B_MAX, B_MAX);
      int c = gen.uniform<int>(-C_MAX, C_MAX);
      printf("%d %d %d %d\n", l, r, b, c);
    }
    else
    {
      int l, r;
      tie(l, r) = gen.uniform_pair(0, n);
      printf("%d %d\n", l, r);
    }
  }
  return 0;
}
