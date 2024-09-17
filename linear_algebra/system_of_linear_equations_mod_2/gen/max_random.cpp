#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = N_MAX;
  auto random_01_str = [&](int n) -> string {
    string S(n, '?');
    for (int i = 0; i < n; ++i) S[i] = '0' + gen.uniform(0, 1);
    return S;
  };

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    string S = random_01_str(m);
    printf("%s\n", S.c_str());
  }
  string S = random_01_str(n);
  printf("%s\n", S.c_str());
  return 0;
}
