#include <iostream>

#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

char make_hex(int x)
{
  assert(0 <= x && x < 16);
  if (x < 10)
    return char('0' + x);
  else
    return char('A' + x - 10);
}

string make_num(Random &gen, int n, bool negative)
{
  string x;
  for (int i = 0; i < n; ++i)
    x += make_hex(gen.uniform<int>(0, 15));
  if (n >= 2)
    x[0] = make_hex(gen.uniform<int>(1, 15));
  if (negative && x != "0")
    x = "-" + x;
  return x;
}

int main(int, char *argv[])
{
  long long seed = atoll(argv[1]);
  auto gen = Random(seed + 1234);

  int t = 1;
  printf("%d\n", t);

  int alen = LOG_16_A_AND_B_MAX;
  int blen = gen.uniform(1LL, LOG_16_A_AND_B_MAX - 1);

  string A = make_num(gen, alen, false);
  string B = make_num(gen, blen, false);

  printf("%s %s\n", A.c_str(), B.c_str());
}
