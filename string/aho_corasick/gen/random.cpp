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

  vector<int> S;

  if (0 <= (seed % 8) && (seed % 8) < 4) {
    // 文字列長 [1,k]
    int ks[] = {1, 2, 10, 100};
    int K = ks[seed % 8];
    int now = 0;
    while (now < MAX_S_SUM) {
      int k = gen.uniform<int>(1, K);
      if (now + k > MAX_S_SUM) continue;
      S.emplace_back(k), now += k;
    }
  } else if (4 <= (seed % 8) && (seed % 8) < 8) {
    // 個数 [1,k]
    int ks[] = {1, 2, 10, 100};
    int K = ks[(seed % 8) - 4];
    vector<int> cut = gen.choice(K - 1, 1, int(MAX_S_SUM - 1));
    cut.insert(cut.begin(), 0);
    cut.emplace_back(MAX_S_SUM);
    assert(int(cut.size()) == K + 1);
    for (int i = 0; i < K; ++i) S.emplace_back(cut[i + 1] - cut[i]);
  } else {
    assert(0);
  }

  int ks[] = {2, 5, 26};
  int sigma = ks[seed % 3];

  vector<string> dat;
  for (int n: S) {
    string X(n, '?');
    for (int i = 0; i < n; ++i) { X[i] = char(gen.uniform<int>(0, sigma - 1) + 'a'); }
    dat.emplace_back(X);
  }

  out(gen, dat);
  return 0;
}
