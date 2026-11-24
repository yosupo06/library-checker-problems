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
    for (int i = 0; i < n; ++i) {
      ll best = -1;
      int answer = -1;
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        ll dx = p[i].x - p[j].x;
        ll dy = p[i].y - p[j].y;
        ll d = dx * dx + dy * dy;
        if (best < d) {
          best = d;
          answer = j;
        }
      }
      if (i) printf(" ");
      printf("%d", answer);
    }
    printf("\n");
  }
  return 0;
}
