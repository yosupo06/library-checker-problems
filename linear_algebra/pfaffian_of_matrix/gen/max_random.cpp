#include <iostream>
#include "random.h"

using namespace std;

int main(int, char *argv[])
{

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(300 - 10, 300);
  vector<vector<int>> a(n * 2, vector<int>(n * 2));
  for (int i = 0; i < n * 2; i++)
  {
    for (int j = i + 1; j < n * 2; j++)
    {
      a[i][j] = gen.uniform(0, 998244353 - 1);
      a[j][i] = (998244353 - a[i][j]) % 998244353;
    }
  }

  printf("%d\n", n);
  for (int i = 0; i < n * 2; i++)
  {
    for (int j = 0; j < n * 2; j++)
    {
      printf("%d", a[i][j]);
      if (j + 1 != n * 2)
        printf(" ");
    }
    printf("\n");
  }
  return 0;
}
