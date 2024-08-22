#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);

  vector<map<int, int>> seg(N + N);
  auto add = [&](int i) -> void {
    int x = A[i];
    i += N;
    while (i) seg[i][x]++, i /= 2;
  };

  auto rm = [&](int i) -> void {
    int x = A[i];
    i += N;
    while (i) seg[i][x]--, i /= 2;
  };

  auto get = [&](int idx, int x) -> int {
    return (seg[idx].count(x) ? seg[idx][x] : 0);
  };

  auto query = [&](int L, int R, int x) -> void {
    int ans = 0;
    L += N, R += N;
    while (L < R) {
      if (L & 1) ans += get(L++, x);
      if (R & 1) ans += get(--R, x);
      L /= 2, R /= 2;
    }
    printf("%d\n", ans);
  };

  for (int i = 0; i < N; ++i) add(i);

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, x;
      scanf("%d %d", &i, &x);
      rm(i), A[i] = x, add(i);
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      query(l, r, x);
    }
  }
  return 0;
}
