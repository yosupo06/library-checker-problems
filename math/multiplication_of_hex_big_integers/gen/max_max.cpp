#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "random.h"
#include "../params.h"

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
  auto gen = Random(seed);

  vector<bool> neg_a = {false, false, true, true};
  vector<bool> neg_b = {false, true, false, true};

  vector<string> A, B;
  int na = LOG_16_A_AND_B_MAX;
  int nb = LOG_16_A_AND_B_MAX;
  string a = make_num(gen, na, neg_a[seed % 4]);
  string b = make_num(gen, nb, neg_b[seed % 4]);
  A.emplace_back(a);
  B.emplace_back(b);

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++)
  {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
