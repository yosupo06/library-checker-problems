#include <cstdio>
#include <cassert>
#include <vector>
#include <tuple>

using namespace std;
using ll = long long;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  assert(N + Q < 10000);

  vector<tuple<int, int, int, int, int>> RECT;
  for (int i = 0; i < N; ++i) {
    int x1, x2, y1, y2, w;
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
    RECT.emplace_back(x1, x2, y1, y2, w);
  }

  for (int i = 0; i < Q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int x1, x2, y1, y2, w;
      scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
      RECT.emplace_back(x1, x2, y1, y2, w);
    }
    if (t == 1) {
      int x, y;
      scanf("%d %d", &x, &y);
      ll ans = 0;
      for (auto& [x1, x2, y1, y2, w]: RECT) {
        if (x1 <= x && x < x2 && y1 <= y && y < y2) { ans += w; }
      }
      printf("%lld\n", ans);
    }
  }

  return 0;
}
