#include <iostream>
#include <vector>

#include "testlib.h"
#include "params.h"

int main()
{
  registerValidation();

  int n = inf.readInt(1, N_MAX);
  inf.readChar('\n');

  std::vector a(n * 2, std::vector<int>(n * 2));
  for (int i = 0; i < n * 2; i++)
  {
    for (int j = 0; j < n * 2; j++)
    {
      a[i][j] = inf.readInt(0, MOD - 1);
      if (j + 1 != n * 2)
        inf.readSpace();
    }
    inf.readChar('\n');
  }
  for (int i = 0; i < n * 2; i++)
  {
    for (int j = 0; j < n * 2; j++)
    {
      ensure(a[j][i] == (MOD - a[i][j]) % MOD);
    }
  }
  inf.readEof();
  return 0;
}
