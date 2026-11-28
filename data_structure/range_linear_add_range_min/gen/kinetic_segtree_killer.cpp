#include <cstdio>
#include <cstdlib>
#include "../params.h"
#include "random.h"

// Apart from the ends, a_i = s i + e_i with 0 <= e_i < noise <= |s|, so the sequence
// is strictly monotone. Each update gives s a random value of the opposite sign, so
// the minimum of every segment moves to the other end and a kinetic segment tree
// recomputes O(N) nodes per update. A query follows every update, so no two updates
// cancel out before the tree is read.
int main(int, char *argv[])
{
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_AND_Q_MAX;
  int q = N_AND_Q_MAX;
  int max_slope = B_MAX / 2;
  int noise = max_slope / 2;
  int s = -gen.uniform(noise, max_slope);
  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++)
  {
    printf("%d", s * i + gen.uniform(0, noise - 1));
    if (i != n - 1)
      printf(" ");
  }
  printf("\n");
  for (int i = 0; i < q; i++)
  {
    if (i % 2 == 0)
    {
      int next = gen.uniform(noise, max_slope);
      if (s > 0)
        next = -next;
      int l = gen.uniform(0, n / 16);
      int r = gen.uniform(n - n / 16, n);
      int c = gen.uniform<int>(-C_MAX, C_MAX);
      printf("0 %d %d %d %d\n", l, r, next - s, c);
      s = next;
    }
    else
    {
      int l = gen.uniform(0, n / 2 - 1);
      int r = gen.uniform(n / 2 + 1, n);
      printf("1 %d %d\n", l, r);
    }
  }
  return 0;
}
