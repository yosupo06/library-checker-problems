#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

// 約数の個数が多いmodを選ぶことにする
// 約数関数の前計算
int sigma[M_MAX + 10], sieve[M_MAX + 10];

void build() {
  for (int i = 2; i * i <= M_MAX; i++) {
    if (sieve[i] == 0) {
      sieve[i] = i;
      for (int j = i * i; j <= M_MAX; j += i) {
        sieve[j] = i;
      }
    }
  }

  sigma[1] = 1;
  for (int i = 2; i <= M_MAX; i++) {
    if (sieve[i] == 0) {
      sigma[i] = 2;
    } else {
      int j = i, c = 0;
      while (j % sieve[i] == 0) j /= sieve[i], c++;
      sigma[i] = sigma[j] * (c + 1);
    }
  }
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

  build();
  int t = T_MAX;
  int m;

  do {
    m = gen.uniform<int>(1, M_MAX);
  } while (sigma[m] < 30);
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
