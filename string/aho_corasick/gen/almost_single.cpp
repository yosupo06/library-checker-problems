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

  int K = ks[(seed % 4)];

  vector<int> S;
  vector<int> cut = gen.choice(K - 1, 1, int(MAX_S_SUM - 1));
  cut.insert(cut.begin(), 0);
  cut.emplace_back(MAX_S_SUM);
  assert(int(cut.size()) == K + 1);
  for (int i = 0; i < K; ++i) S.emplace_back(cut[i + 1] - cut[i]);

  char ch = gen.uniform<char>('a', 'z');
  vector<string> dat;
  for (int n: S) {
    string X(n, ch);
    int k = gen.uniform<int>(1, 3);
    X[k] = gen.uniform<char>('a', 'z');
    dat.emplace_back(X);
  }

  out(gen, dat);
  return 0;
}
