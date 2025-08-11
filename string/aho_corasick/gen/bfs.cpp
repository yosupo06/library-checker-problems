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

  int ks[] = {1, 2, 5, 26};
  int k = ks[seed % 4];

  int now = 0;
  vector<string> dat;
  dat.emplace_back("");
  for (int i = 0;; ++i) {
    string S = dat[i];
    if (now + (S.size()) + 1 > MAX_S_SUM) break;
    for (int c = 0; c < k; ++c) {
      string nxt = char('a' + c) + S;
      if (now + (nxt.size()) <= MAX_S_SUM) {
        now += nxt.size();
        dat.emplace_back(nxt);
      }
    }
  }
  dat.erase(dat.begin());
  out(gen, dat);

  return 0;
}
