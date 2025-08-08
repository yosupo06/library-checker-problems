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
    } else if (t == 2 || t == 3) {
      printf("%d\n", t);
      --n;
    } else if (t == 4) {
      int i = gen.uniform<int>(0, n - 1);
      printf("%d %d\n", t, i);
    } else {
      assert(false);
    }
  }
}

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int Q = MAX_Q;

  int prob[5];
  if (seed <= 2) {
    prob[0] = prob[1] = prob[2] = prob[3] = prob[4] = 20;
  } else if (seed == 3) {
    prob[0] = 96;
    prob[1] = prob[2] = prob[3] = prob[4] = 1;
  } else if (seed == 4) {
    prob[1] = 96;
    prob[0] = prob[2] = prob[3] = prob[4] = 1;
  } else if (seed == 5) {
    prob[2] = 96;
    prob[0] = prob[1] = prob[3] = prob[4] = 1;
  } else if (seed == 6) {
    prob[3] = 96;
    prob[0] = prob[1] = prob[2] = prob[4] = 1;
  } else if (seed == 7) {
    prob[4] = 96;
    prob[0] = prob[1] = prob[2] = prob[3] = 1;
  } else if (seed == 8) {
    prob[0] = prob[1] = prob[4] = 32;
    prob[2] = prob[3] = 2;
  } else {
    while (1) {
      prob[0] = gen.uniform<int>(0, 100);
      prob[1] = gen.uniform<int>(0, 100);
      prob[2] = gen.uniform<int>(0, 100);
      prob[3] = gen.uniform<int>(0, 100);
      prob[4] = gen.uniform<int>(0, 100);
      if (prob[0] + prob[1] + prob[2] + prob[3] + prob[4] > 0) break;
    }
  }

  vector<int> S;
  for (int k = 0; k < 5; ++k) {
    for (int i = 0; i < prob[k]; ++i) S.push_back(k);
  }

  vector<int> T(Q);
  int n = 0;
  for (int q = 0; q < Q; ++q) {
    int idx = gen.uniform<int>(0, int(S.size()) - 1);
    int t = S[idx];
    if (n == 0) t = gen.uniform<int>(0, 1);
    T[q] = t;
    if (t == 0 || t == 1) ++n;
    if (t == 2 || t == 3) --n;
  }

  out(T, gen);
  return 0;
}