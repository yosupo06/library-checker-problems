#include <cassert>
#include <cstdio>
#include <limits>
#include <vector>

using namespace std;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
  vector<int> c(n + m - 1, numeric_limits<int>::max());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = a[i] + b[j];
      if (c[i + j] > x) c[i + j] = x;
    }
  }
  for (int k = 0; k < n + m - 1; ++k) {
    if (k) printf(" ");
    printf("%d", c[k]);
  }
  return 0;
}
