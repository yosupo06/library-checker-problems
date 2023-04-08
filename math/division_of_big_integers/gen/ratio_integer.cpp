/**
 * |B| * m = |A|, m : half integer
 */

#include <iostream>

#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed + 123);

  int m = vector{2, 3, 5, 10, 20, 50}[seed % 6];
  int t = 2;
  printf("%d\n", t);
  int blen = SUM_OF_CHARACTER_LENGTH / ((m + 1) * t);
  int alen = blen * m;

  for (int _ = 0; _ < t; _++) {
    string A, B;
    for (int i = 0; i < alen; i++) {
      int lower = i == 0 ? 1 : 0;
      A.push_back('0' + gen.uniform(lower, 9));
    }
    for (int i = 0; i < blen; i++) {
      int lower = i == 0 ? 1 : 0;
      B.push_back('0' + gen.uniform(lower, 9));
    }
    printf("%s %s\n", A.c_str(), B.c_str());
  }
}
