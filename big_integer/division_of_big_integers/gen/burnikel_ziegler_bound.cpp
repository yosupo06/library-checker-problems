/**
 *  |A| % |B| nearly equals to 0.
 */

#include <iostream>

#include "../base.hpp"
#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char *argv[])
{
  ll seed = atoll(argv[1]);

  bigint base;
  if (seed % 4 == 0)
    base = 10;
  else if (seed % 4 == 1)
    base = 1000000000;
  else if (seed % 4 == 2)
    base = 2;
  else if (seed % 4 == 3)
    base = 1LL << 32;

  int lsum = 0;
  vector<string> A, B;
  bigint bb = base;

  while (true)
  {
    bigint quotient = 2 * bb * bb - 1;
    bigint remainder = (bb - 1) * bb;
    bigint y = remainder + 1;
    bigint x = quotient * y + remainder;

    string sa = x.to_string();
    string sb = y.to_string();

    lsum += sa.size() + sb.size();
    if (lsum > SUM_OF_CHARACTER_LENGTH)
      break;
    A.push_back(sa);
    B.push_back(sb);

    bb *= base;
  }

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++)
  {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}