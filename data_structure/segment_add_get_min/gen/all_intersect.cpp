#include <stdio.h>
#include "../params.h"
#include "random.h"

void conquer(int l, int r, int &cnt) {
  if (r - l <= 10000) return;
  int mid = (l + r) / 2;
  if (cnt > 0) conquer(l, mid, cnt);
  if (cnt > 0) conquer(mid + 1, r, cnt);
  if (cnt > 0) {
    printf("%d %d 0 %d\n", l, r + 1, mid);
    cnt--;
  }
}

int main(int, char **) {
  const int N = N_AND_Q_MAX;
  const int Q = N_AND_Q_MAX;
 
  int cnt = N;
  printf("%d %d\n", N, Q);
  conquer(-A_ABS_MAX, A_ABS_MAX-1, cnt);
  
  for (int q = 0; q < Q - 1; ++q) {
    printf("0 %lld %lld 1 0\n", -A_ABS_MAX, A_ABS_MAX);
  }
  printf("1 0\n");
  return 0;
}
