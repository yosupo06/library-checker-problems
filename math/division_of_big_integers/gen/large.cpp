#include <iostream>

#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed + 1234);

  vector<string> A, B;
  int lsum = 0;

  while (true) {
    string sa, sb;
    int alen = gen.uniform(1, 100000);
    int blen = gen.uniform(1, 100000);
    // mostly |A| >= |B|
    if (gen.uniform(0, 9)) {
      if (alen < blen) swap(alen, blen);
    }
    // A can be 0
    for (int i = 0; i < alen; i++) {
      int lower = (alen != 1 and i == 0) ? 1 : 0;
      sa.push_back('0' + gen.uniform(lower, 9));
    }
    for (int i = 0; i < blen; i++) {
      int lower = i == 0 ? 1 : 0;
      sb.push_back('0' + gen.uniform(lower, 9));
    }
    if (gen.uniform_bool() and sa != "0") sa.insert(begin(sa), '-');
    if (gen.uniform_bool()) sb.insert(begin(sb), '-');
    lsum += sa.size() + sb.size();
    if (lsum > SUM_OF_CHARACTER_LENGTH) break;
    A.push_back(sa);
    B.push_back(sb);
  }

  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
