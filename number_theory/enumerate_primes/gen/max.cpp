#include <stdio.h>
#include <vector>
#include "../params.h"
#include "random.h"

using std::vector;

// floor(sqrt(a))
long long floorSqrt(long long a) {
  long long b = a, x = 0, y = 0;
  for (int e = (63 - __builtin_clzll(a)) & ~1; e >= 0; e -= 2) {
    x <<= 1;
    y <<= 1;
    if (b >= (y | 1) << e) {
      b -= (y | 1) << e;
      x |= 1;
      y += 2;
    }
  }
  return x;
}

// \pi(N)
long long numPrimes(long long N) {
  const long long sqrtN = floorSqrt(N);
  vector<long long> small(sqrtN + 1), large(sqrtN + 1);
  auto get = [&](long long n) {
    return (n <= sqrtN) ? small[n] : large[N / n];
  };
  for (long long n = 1; n <= sqrtN; ++n) small[n] = n;
  for (long long l = 1; l <= sqrtN; ++l) large[l] = N / l;
  vector<bool> isnp(sqrtN + 1, false);
  for (long long p = 2; p <= sqrtN; ++p) {
    if (!isnp[p]) {
      for (long long n = p * p; n <= sqrtN; n += p) isnp[n] = true;
      for (long long l = 1; l <= sqrtN; ++l) {
        const long long n = N / l;
        if (n < p * p) break;
        large[l] -= (get(n / p) - get(p - 1));
      }
      for (long long n = sqrtN; n >= 1; --n) {
        if (n < p * p) break;
        small[n] -= (get(n / p) - get(p - 1));
      }
    }
  }
  return large[1] - 1;
}

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  const long long N = N_MAX;
  const long long pi = numPrimes(N);
  const long long A = pi / X_MAX + 1;
  const long long B =
      (seed == 0) ? 0 : (seed == 1) ? ((pi - 1) % A) : rng.uniform(0LL, A - 1);
  printf("%lld %lld %lld\n", N, A, B);
  return 0;
}
