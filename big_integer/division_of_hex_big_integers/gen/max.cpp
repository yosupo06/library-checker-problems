#include <iostream>

#include "../params.h"
using namespace std;
using ll = long long;

int main(int, char *argv[])
{
  long long seed = atoll(argv[1]);

  string max(LOG_16_A_AND_B_MAX, 'F');
  string max_minus_one(LOG_16_A_AND_B_MAX, 'F');

  max_minus_one[LOG_16_A_AND_B_MAX - 1] = 'E';

  int t = 1;
  string A, B;
  switch ((seed % 3 + 3) % 3)
  {
  case 0:
    A = B = max;
    break;
  case 1:
    A = max, B = "1";
    break;
  case 2:
    A = max_minus_one, B = max;
    break;
  }
  printf("%d\n", t);
  printf("%s %s\n", A.c_str(), B.c_str());
}
