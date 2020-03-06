#include <assert.h>
#include <stdio.h>
#include <bitset>

using std::bitset;

// Sieve <= lim (<= LIM_SIEVE)
// isPrime[n]: 2 n + 1
constexpr int LIM_SIEVE = 500'000'010;
bitset<((LIM_SIEVE + 1) >> 1)> isPrime;
void sieveOfAtkin(int lim) {
  assert(lim <= LIM_SIEVE);
  lim = (lim + 1) >> 1;
  // n == 1, 5 (mod 4): 4 x^2 + y^2
  //   x == 0 (mod 3), y == 1, 5 (mod 6)
  //   x == 1, 2 (mod 3), y == 1 (mod 2)
  for (int y = 1, m; (m = (y * y + 36) >> 1) < lim; y += 2) {
    if (y % 3 != 0) {
      for (int k = 0; m < lim; m += (k += 36) + 18) isPrime.flip(m);
    }
  }
  for (int x = 1, m; (m = (4 * x * x + 1) >> 1) < lim; ++x) {
    if (x % 3 != 0) {
      for (int k = 0; m < lim; m += (k += 4)) isPrime.flip(m);
    }
  }
  // n == 7 (12): 3 x^2 + y^2
  //   x == 1 (2), y == 2, 4 (6)
  for (int y = 2, m; (m = (y * y + 3) >> 1) < lim; y += 2) {
    if (y % 3 != 0) {
      for (int k = 0; m < lim; m += (k += 12)) isPrime.flip(m);
    }
  }
  // n == 11 (12): 3 x^2 - y^2 (x > y)
  //   x == 0 (2), y == 1, 5 (6)
  //   x == 1 (2), y == 2, 4 (6)
  for (int y = 1, m; (m = ((2 * y + 6) * y + 3) >> 1) < lim; ++y) {
    if (y % 3 != 0) {
      for (int k = 6 * y; m < lim; m += (k += 12)) isPrime.flip(m);
    }
  }
  // non square-free
  for (int p = 5, p2; (p2 = p * p) >> 1 < lim; p += 2) {
    if (isPrime[p >> 1]) {
      for (int m = p2 >> 1; m < lim; m += p2) isPrime.reset(m);
    }
  }
  // 3
  if (1 < lim) isPrime.set(1);
}

int anssLen;
int anss[1'000'010];

int main() {
  int N, A, B;
  scanf("%d%d%d", &N, &A, &B);
  sieveOfAtkin(N);
  int pi = 0;
  if (2 <= N) {
    if (pi++ % A == B) {
      anss[anssLen++] = 2;
    }
  }
  for (int n = 3; n <= N; n += 2) {
    if (isPrime[n >> 1]) {
      if (pi++ % A == B) {
        anss[anssLen++] = n;
      }
    }
  }
  printf("%d %d\n", pi, (pi + A - 1 - B) / A);
  for (int i = 0; i < anssLen; ++i) {
    if (i > 0) printf(" ");
    printf("%d", anss[i]);
  }
  puts("");
  return 0;
}
