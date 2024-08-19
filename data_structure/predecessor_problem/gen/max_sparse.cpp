#include <iostream>
#include <string>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int Q = Q_MAX;
  printf("%d %d\n", N, Q);
  string T(N, ' ');
  for (auto& c : T) {
    c = '0';
    if (gen.uniform(1, 1000000) == 1) c = '1';
  }
  printf("%s\n", T.c_str());
  for (int i = 0; i < Q; i++) {
    int c = gen.uniform(3, 4);
    int k = gen.uniform(0, N - 1);
    printf("%d %d\n", c, k);
  }
  return 0;
}
