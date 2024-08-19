#include <iostream>
#include <string>

#include "../params.h"

using namespace std;

int main(int, char**) {
  int N = 64 * 64 + 1;
  int Q = N * 4 - 1;
  printf("%d %d\n", N, Q);
  string T(N, '0');
  T[2048] = '1';
  printf("%s\n", T.c_str());
  for (int c = 1; c <= 4; c++) {
    for (int k = 0; k < N; k++) {
      if (c == 1 and T[k] == '1') continue;
      printf("%d %d\n", c, k);
    }
  }
  return 0;
}
