#include "random.h"
#include "../params.h"
#include <cstdio>
#include <vector>

using namespace std;

void out(vector<int> T, Random &gen) {
  int Q = T.size();
  printf("%d\n", Q);
  int n = 0;
  for (int t : T) {
    if (t == 0 || t == 1) {
      int x = gen.uniform<int>(MIN_X, MAX_X);
      printf("%d %d\n", t, x);
      ++n;
    }
    if (t == 2 || t == 3) {
      printf("%d\n", t);
      --n;
    }
    if (t == 4) {
      int i = gen.uniform<int>(0, n - 1);
      printf("%d %d\n", t, i);
    }
  }
}

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int Q = gen.uniform<int>(MIN_Q, MAX_Q);

  vector<int> T(Q);

  int n = 0;
  for (int q = 0; q < Q; ++q) {
    int t = gen.uniform<int>(0, 4);
    if (n == 0) t = gen.uniform<int>(0, 1);
    T[q] = t;
    if (t == 0 || t == 1) ++n;
    if (t == 2 || t == 3) --n;
  }
  out(T, gen);
  return 0;
}