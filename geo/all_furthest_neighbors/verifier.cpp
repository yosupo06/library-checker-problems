#include <algorithm>
#include <numeric>
#include <vector>

#include "params.h"
#include "testlib.h"

using namespace std;
using ll = long long;

struct Point {
  ll x, y;
};

__int128 cross(const Point& a, const Point& b, const Point& c) {
  return __int128(b.x - a.x) * (c.y - a.y) -
         __int128(b.y - a.y) * (c.x - a.x);
}

int main() {
  registerValidation();

  int T = inf.readInt(1, T_MAX);
  inf.readChar('\n');

  ll sum_n = 0;
  for (int t = 0; t < T; ++t) {
    int n = inf.readInt(3, SUM_N_MAX);
    inf.readChar('\n');
    sum_n += n;
    ensuref(sum_n <= SUM_N_MAX, "the sum of N exceeds the limit");

    vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
      p[i].x = inf.readLong(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
      inf.readSpace();
      p[i].y = inf.readLong(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
      inf.readChar('\n');
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
      if (p[i].x != p[j].x) return p[i].x < p[j].x;
      if (p[i].y != p[j].y) return p[i].y < p[j].y;
      return i < j;
    });
    for (int i = 1; i < n; ++i) {
      ensuref(p[order[i - 1]].x != p[order[i]].x ||
                  p[order[i - 1]].y != p[order[i]].y,
              "duplicate vertices in testcase %d", t);
    }

    vector<int> hull;
    for (int phase = 0; phase < 2; ++phase) {
      size_t base = hull.size();
      for (int k = 0; k < n; ++k) {
        int v = order[phase == 0 ? k : n - 1 - k];
        while (hull.size() >= base + 2 &&
               cross(p[hull[hull.size() - 2]], p[hull.back()], p[v]) <= 0) {
          hull.pop_back();
        }
        hull.push_back(v);
      }
      hull.pop_back();
    }

    ensuref(int(hull.size()) == n,
            "the points do not form a strictly convex polygon in testcase %d",
            t);
    int start = hull[0];
    for (int i = 0; i < n; ++i) {
      ensuref(hull[i] == (start + i) % n,
              "the vertices are not in counterclockwise order in testcase %d",
              t);
    }
  }

  inf.readEof();
  return 0;
}
