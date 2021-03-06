#include <iostream>
#include <string>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform(4095, 4097);
  int Q = 100000;
  printf("%d %d\n", N, Q);
  string T(N, ' ');
  for (auto& c : T) c = '0' + gen.uniform(0, 1);
  printf("%s\n", T.c_str());
  for (int i = 0; i < Q; i++) {
    int c = gen.uniform(0, 4);
    int k = gen.uniform(0, N - 1);
    printf("%d %d\n", c, k);
  }
  return 0;
}
