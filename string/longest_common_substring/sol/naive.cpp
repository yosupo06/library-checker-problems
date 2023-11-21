#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main() {
  static char buf[1'000'000];
  string s, t;
  scanf("%s", buf);
  s = buf;
  scanf("%s", buf);
  t = buf;

  int ans = 0;
  tuple<int, int, int, int> ANS = {0, 0, 0, 0};
  int n = s.size(), m = t.size();

  for (int a = 0; a < n; ++a) {
    for (int c = 0; c < m; ++c) {
      for (int k = 1; k <= min(n - a, m - c); ++k) {
        string X = s.substr(a, k);
        string Y = t.substr(c, k);
        if (X == Y && ans < k) {
          ans = k;
          ANS = {a, a + k, c, c + k};
        }
      }
    }
  }
  auto [a, b, c, d] = ANS;
  printf("%d %d %d %d\n", a, b, c, d);
  return 0;
}
