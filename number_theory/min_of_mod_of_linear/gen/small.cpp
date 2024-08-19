#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  seed %= 10;

  int T = 0;
  int LIM = 40;

  for (int N = 1; N <= LIM; ++N) {
    for (int M = 1; M <= LIM; ++M) {
      for (int A = 0; A < M; ++A) {
        for (int B = 0; B < M; ++B) {
          if (N % 10 == seed) { ++T; }
        }
      }
    }
  }

  printf("%d\n", T);
  for (int N = 1; N <= LIM; ++N) {
    for (int M = 1; M <= LIM; ++M) {
      for (int A = 0; A < M; ++A) {
        for (int B = 0; B < M; ++B) {
          if (N % 10 == seed) { printf("%d %d %d %d\n", N, M, A, B); }
        }
      }
    }
  }

  return 0;
}
