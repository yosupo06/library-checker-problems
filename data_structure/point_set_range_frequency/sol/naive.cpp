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

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, x;
      scanf("%d %d", &i, &x);
      A[i] = x;
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      int ans = 0;
      for (int i = l; i < r; ++i) ans += (A[i] == x);
      printf("%d\n", ans);
    }
  }
  return 0;
}
