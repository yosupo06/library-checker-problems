#include "testlib.h"
#include <assert.h>
#include <vector>
#include "params.h"

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

int main() {
  assert(numPrimes(1) == 0);
  assert(numPrimes(2) == 1);
  assert(numPrimes(3) == 2);
  assert(numPrimes(4) == 2);
  assert(numPrimes(5) == 3);
  assert(numPrimes(6) == 3);
  assert(numPrimes(7) == 4);
  assert(numPrimes(8) == 4);
  assert(numPrimes(9) == 4);
  assert(numPrimes(10) == 4);
  assert(numPrimes(100) == 25);
  assert(numPrimes(1'000) == 168);
  assert(numPrimes(10'000) == 1'229);
  assert(numPrimes(100'000) == 9'592);
  assert(numPrimes(1'000'000) == 78'498);
  assert(numPrimes(10'000'000) == 664'579);
  assert(numPrimes(100'000'000) == 5'761'455);
  assert(numPrimes(1'000'000'000) == 50'847'534);
  // assert(numPrimes(10'000'000'000LL) == 455'052'511);
  // assert(numPrimes(100'000'000'000LL) == 4'118'054'813LL);
  // assert(numPrimes(1'000'000'000'000LL) == 37'607'912'018LL);

  registerValidation();
  const long long N = inf.readLong(N_MIN, N_MAX, "N");
  inf.readChar(' ');
  const long long A = inf.readLong(1, N, "A");
  inf.readChar(' ');
  const long long B = inf.readLong(0, N - 1, "B");
  inf.readChar('\n');
  inf.readEof();

  const long long pi = numPrimes(N);
  ensuref(A * X_MAX + B >= pi, "X <= " I64 " must hold", X_MAX);
  return 0;
}
