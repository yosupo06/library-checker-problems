#include <cstdio>
#include <cassert>
#include <vector>
#include <tuple>

using namespace std;
using ll = long long;

const int MAX = 50;
ll A[MAX][MAX];

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  auto add = [&](int x1, int x2, int y1, int y2, int w) -> void {
    assert(x2 <= MAX && y2 <= MAX);
    for (int x = x1; x < x2; ++x) {
      for (int y = y1; y < y2; ++y) { A[x][y] += w; }
    }
  };

  for (int i = 0; i < N; ++i) {
    int x1, x2, y1, y2, w;
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
    add(x1, x2, y1, y2, w);
  }

  for (int i = 0; i < Q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int x1, x2, y1, y2, w;
      scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
      add(x1, x2, y1, y2, w);
    }
    if (t == 1) {
      int x, y;
      scanf("%d %d", &x, &y);
      ll ans = 0;
      if (x < MAX && y < MAX) ans = A[x][y];
      printf("%lld\n", ans);
    }
  }

  return 0;
}
