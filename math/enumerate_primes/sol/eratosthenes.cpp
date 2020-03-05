#include <stdio.h>
#include <bitset>

using std::bitset;

bitset<500'000'010> isnp;

int anssLen;
int anss[1'000'010];

int main() {
  int N, A, B;
  scanf("%d%d%d", &N, &A, &B);

  for (int p = 2; p <= N; ++p) {
    if (!isnp[p]) {
      for (int n = 2 * p; n <= N; n += p) {
        isnp[n] = true;
      }
    }
  }

  int pi = 0;
  for (int n = 2; n <= N; ++n) {
    if (!isnp[n]) {
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
