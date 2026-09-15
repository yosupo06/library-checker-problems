#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

struct Point {
  ll x, y;
};

// Returns the leftmost maximum in every row of a monotone matrix.
template <class F>
vector<int> monotone_maxima(int h, int w, F value) {
  vector<int> max_col(h);
  auto dfs = [&](auto&& self, int row_l, int row_r, int col_l,
                 int col_r) -> void {
    if (row_l == row_r) return;
    int row = (row_l + row_r) / 2;
    int best = col_l;
    for (int col = col_l + 1; col < col_r; ++col) {
      if (value(row, best) < value(row, col)) best = col;
    }
    max_col[row] = best;
    self(self, row_l, row, col_l, best + 1);
    self(self, row + 1, row_r, best, col_r);
  };
  dfs(dfs, 0, h, 0, w);
  return max_col;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<Point> p(n);
    for (Point& q : p) scanf("%lld %lld", &q.x, &q.y);

    auto value = [&](int i, int j) -> ll {
      if (j <= i) return j - i;
      if (j >= i + n) return -1;
      ll dx = p[i].x - p[j % n].x;
      ll dy = p[i].y - p[j % n].y;
      return dx * dx + dy * dy;
    };

    vector<int> answer = monotone_maxima(n, 2 * n - 1, value);
    for (int i = 0; i < n; ++i) {
      if (i) printf(" ");
      printf("%d", answer[i] % n);
    }
    printf("\n");
  }
  return 0;
}
