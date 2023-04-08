#include <iostream>

#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  int sgn_a = vector{1, 1, -1, -1}[seed % 4];
  int sgn_b = vector{1, -1, 1, -1}[seed % 4];
  string MAX(LOG_10_A_AND_B_MAX + 1, '0');
  MAX[0] = '1';

  int t = 1;
  string A = MAX, B = MAX;
  if (sgn_a == -1) A.insert(begin(A), '-');
  if (sgn_b == -1) B.insert(begin(B), '-');

  printf("%d\n", t);
  printf("%s %s\n", A.c_str(), B.c_str());
}
