/**
 *  |A| % |B| nearly equals to 0.
 */

#include <iostream>

#include "../base.hpp"
#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed + 12345678);

  int upper = vector{10, 1000, 100000}[seed % 3];

  vector<string> A, B;
  int lsum = 0;

  while (true) {
    string sa, sb;
    int alen = gen.uniform(1, upper);
    int blen = gen.uniform(1, upper);
    // mostly |A| >= |B|
    if (alen < blen) swap(alen, blen);
    // A can be 0
    for (int i = 0; i < alen; i++) {
      int lower = (alen != 1 and i == 0) ? 1 : 0;
      sa.push_back('0' + gen.uniform(lower, 9));
    }
    for (int i = 0; i < blen; i++) {
      int lower = i == 0 ? 1 : 0;
      sb.push_back('0' + gen.uniform(lower, 9));
    }

    bigint x = sa, y = sb;
    x = x / y * y;
    int cmd = gen.uniform(0, 3);
    if (cmd == 0) {
      // do nothing
    } else if (cmd == 1) {
      x += 1;
    } else if (cmd == 2) {
      x -= 1;
    } else {
      long long range = upper <= 10 ? 100000LL : 10000000000LL;
      x += gen.uniform(-range, range);
    }
    sa = x.to_string();

    lsum += sa.size() + sb.size();
    if (lsum > SUM_OF_CHARACTER_LENGTH) break;
    if (x >= 0) {
      A.push_back(sa);
      B.push_back(sb);
    } else {
      lsum -= sa.size() + sb.size();
    }
  }

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
