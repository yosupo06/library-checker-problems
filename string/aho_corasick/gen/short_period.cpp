#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

void out(Random& gen, vector<string> dat) {
  gen.shuffle(dat.begin(), dat.end());
  int n = dat.size();
  printf("%d\n", n);
  for (auto& x: dat) printf("%s\n", x.c_str());
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  // 個数
  int ks[] = {1, 2, 10, 100};
  // 周期
  int ps[] = {2, 3, 10, 100};

  int K = ks[(seed % 4)];
  int P = ps[(seed / 4) % 4];

  vector<int> S;
  vector<int> cut = gen.choice(K - 1, 1, int(MAX_S_SUM - 1));
  cut.insert(cut.begin(), 0);
  cut.emplace_back(MAX_S_SUM);
  assert(int(cut.size()) == K + 1);
  for (int i = 0; i < K; ++i) S.emplace_back(cut[i + 1] - cut[i]);

  string base;
  for (int i = 0; i < P; ++i) base += char('a' + gen.uniform<int>(0, 25));
  string X;
  while (int(X.size()) < MAX_S_SUM) X += base;

  vector<string> dat;
  int L = 0;
  for (int n: S) {
    dat.emplace_back(X.substr(L, n));
    L += n;
  }

  out(gen, dat);
  return 0;
}
