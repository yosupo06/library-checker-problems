#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

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

std::vector<int> factors(int m) {
  std::vector<int> res;
  for (int i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      while (m % i == 0) m /= i;
      res.push_back(i);
    }
  }
  if (m != 1) res.push_back(m);
  return res;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = 510510;
  printf("%d %d\n", t, m);

  auto fs = factors(m);

  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<long long>(0, N_MAX);
      k = gen.uniform<long long>(0, N_MAX);
    } while (n < k);
    if (gen.uniform01() > 0.2) {
      // 答えが0になるのを避ける
      modify(n, k, fs[gen.uniform<int>(0, (int)fs.size() - 1)]);
    }
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
