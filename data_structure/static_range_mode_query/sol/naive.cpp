#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) { scanf("%d", &A[i]); }

  for (int q = 0; q < Q; ++q) {
    int L, R;
    scanf("%d %d", &L, &R);
    map<int, int> MP;
    for (int i = L; i < R; ++i) MP[A[i]]++;
    int max = 0, argmax = 0;
    for (auto &[a, b]: MP) {
      if (max < b) max = b, argmax = a;
    }
    printf("%d %d\n", argmax, max);
  }
}

signed main() {
  solve();
  return 0;
}
