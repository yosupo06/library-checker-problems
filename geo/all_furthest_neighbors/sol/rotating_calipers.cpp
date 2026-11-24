#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

struct Point {
  ll x, y;
};

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<Point> p(n);
    for (Point& q : p) scanf("%lld %lld", &q.x, &q.y);

    auto dist = [&](int i, int j) -> ll {
      ll dx = p[i].x - p[j % n].x;
      ll dy = p[i].y - p[j % n].y;
      return dx * dx + dy * dy;
    };

    int j = 1;
    for (int i = 0; i < n; ++i) {
      j = max(j, i + 1);
      while (j + 1 < i + n && dist(i, j) < dist(i, j + 1)) ++j;
      if (i) printf(" ");
      printf("%d", j % n);
    }
    printf("\n");
  }
  return 0;
}
