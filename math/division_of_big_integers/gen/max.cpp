#include <iostream>

#include "../base.hpp"
#include "../params.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  string max(LOG_10_A_AND_B_MAX + 1, '0');
  max[0] = '1';

  int t = 1;
  bigint MAX = max, A, B;
  switch ((seed % 3 + 3) % 3) {
    case 0:
      A = B = MAX;
      break;
    case 1:
      A = MAX, B = 1;
      break;
    case 2:
      A = MAX - 1, B = MAX;
      break;
  }
  printf("%d\n", t);
  printf("%s %s\n", A.to_string().c_str(), B.to_string().c_str());
}
