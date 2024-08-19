#include <algorithm>
#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

// 答えが0にならないように調整する
// Kummerの定理より(n-k)とkのp進における加算で繰り上がりが発生しなければよい
void modify(long long& n, long long& k, int p) {
  long long r = n - k;
  n = r;
  std::vector<int> ks;
  while (r != 0 || k != 0) {
    int r0 = r % p, k0 = k % p;
    ks.push_back(std::min<int>(k0, p - 1 - r0));
    r /= p, k /= p;
  }
  k = 0;
  for (int i = ks.size(); i--;) {
    k = k * p + ks[i];
  }
  n += k;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = -1;
  do {
    m = gen.uniform<int>(0, M_MAX);
  } while (!is_prime(m));
  printf("%d %d\n", t, m);

  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<long long>(0, N_MAX);
      k = gen.uniform<long long>(0, N_MAX);
    } while (n < k);
    if (gen.uniform01() >= 0.2) {
      modify(n, k, m);
    }
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
