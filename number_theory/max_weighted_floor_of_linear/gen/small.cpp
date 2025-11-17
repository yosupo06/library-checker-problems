#include <cstdio> // printf
#include <cstdlib> // atoll

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  ll seed = atoll(argv[1]);
  seed %= 10;

  int T = 0;
  ll LIM = 9;

  for (ll N = 1; N <= LIM; ++N) {
    for (ll M = 1; M <= LIM; ++M) {
      for (ll A = -LIM; A <= LIM; ++A) {
        for (ll B = -LIM; B <= LIM; ++B) {
          for (ll C = 0; C < M; ++C) {
            for (ll D = 0; D < M; ++D) {
              if ((N + M + A + B + C + D + LIM * 2) % 10 == seed) { ++T; }
            }
          }
        }
      }
    }
  }

  printf("%d\n", T);
  for (ll N = 1; N <= LIM; ++N) {
    for (ll M = 1; M <= LIM; ++M) {
      for (ll A = -LIM; A <= LIM; ++A) {
        for (ll B = -LIM; B <= LIM; ++B) {
          for (ll C = 0; C < M; ++C) {
            for (ll D = 0; D < M; ++D) {
              if ((N + M + A + B + C + D + LIM * 2) % 10 == seed) {
                printf("%lld %lld %lld %lld %lld %lld\n", N, M, A, B, C, D);
              }
            }
          }
        }
      }
    }
  }

  return 0;
}
