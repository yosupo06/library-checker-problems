#include <iostream>

#include "../params.h"
using namespace std;
using ll = long long;

int main(int, char**) {
  string MAX(LOG_10_A_AND_B_MAX + 1, '0');
  MAX[0] = '1';

  int t = 1;
  string A = MAX, B = MAX;
  printf("%d\n", t);
  printf("%s %s\n", A.c_str(), B.c_str());
}
