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
  vector<string> A, B;
  int sm = 0;

  A.emplace_back("1");
  B.emplace_back("1");

  for (int t = 0; t < T_MAX - 1; ++t)
  {
    int length = t / 3 + 3;
    string a(length, '0');
    a[0] = '1';

    string b = seed ? "-" : "";

    switch (t % 3)
    {
    case 0:
      b += "10";
      break;
    case 1:
      b += a.substr(0, length / 2);
      break;
    default:
      b += a;
      break;
    }

    if (sm + a.size() + b.size() > SUM_OF_CHARACTER_LENGTH)
    {
      break;
    }
    sm += a.size() + b.size();
    A.emplace_back(a);
    B.emplace_back(b);
  }

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++)
  {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
