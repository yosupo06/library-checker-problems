#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; i++) { scanf("%d", &A[i]); }

  for (int i = 0; i < Q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    set<int> S = {A.begin() + l, A.begin() + r};
    int ans = S.size();
    printf("%d\n", ans);
  }
  return 0;
}
