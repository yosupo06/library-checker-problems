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
  auto gen = Random(seed + 12345);

  int upper = vector<int>{10, 300, 10000}[seed % 3];

  vector<string> A, B;
  int lsum = 0;
  while (true)
  {
    int alen = gen.uniform(1, upper);
    int blen = gen.uniform(1, upper);
    // mostly |A| >= |B|
    if (gen.uniform(0, 9))
    {
      if (alen < blen)
        swap(alen, blen);
    }

    // A can be 0
    string sa = make_num(gen, alen, false);
    string sb;
    do
    {
      sb = make_num(gen, alen, false);
    } while (sb == "0");

    lsum += sa.size() + sb.size();
    if (lsum > SUM_OF_CHARACTER_LENGTH)
      break;
    A.push_back(sa);
    B.push_back(sb);
  }

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++)
  {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
