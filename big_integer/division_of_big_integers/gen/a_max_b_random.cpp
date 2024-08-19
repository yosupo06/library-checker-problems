#include <iostream>

#include "../params.h"
#include "random.h"
using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed + 1234);

  int t = 1;
  printf("%d\n", t);

  string A, B;
  int alen = LOG_10_A_AND_B_MAX;
  int blen = gen.uniform(1LL, LOG_10_A_AND_B_MAX);
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
