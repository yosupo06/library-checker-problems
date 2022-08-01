#include <iostream>

#include "../params.h"
#include "random.h"

void modify_2(long long& n, long long& k, Random& gen) {
  long long r = n - k;
  n = r;
  std::vector<int> ks;
  while (r != 0 || k != 0) {
    int r0 = r & 1, k0 = k & 1;
    int nk = k0;
    // 3回に2回はmodifyする
    if (gen.uniform<int>(0, 2) != 0) {
      nk = std::min<int>(k0, 1 - r0);
    }
    ks.push_back(nk);
    r >>= 1, k >>= 1;
  }
  k = 0;
  for (int i = ks.size(); i--;) {
    k = (k << 1) + ks[i];
  }
  n += k;
}

// 524288 = 2^19
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = 524288;
  printf("%d %d\n", t, m);

  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<long long>(0, N_MAX);
      k = gen.uniform<long long>(0, N_MAX);
    } while (n < k);
    modify_2(n, k, gen);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
