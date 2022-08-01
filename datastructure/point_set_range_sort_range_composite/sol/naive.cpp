#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  using T = tuple<int, int, int>;
  vector<T> dat;

  for (int n = 0; n < N; ++n) {
    int p, a, b;
    scanf("%d %d %d", &p, &a, &b);
    dat.emplace_back(p, a, b);
  }

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, p, a, b;
      scanf("%d %d %d %d", &i, &p, &a, &b);
      dat[i] = {p, a, b};
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      for (int i = l; i < r; ++i) {
        auto [p, a, b] = dat[i];
        x = ((long long)(a)*x + b) % MOD;
      }
      printf("%d\n", x);
    }
    if (t == 2) {
      int l, r;
      scanf("%d %d", &l, &r);
      sort(dat.begin() + l, dat.begin() + r);
    }
    if (t == 3) {
      int l, r;
      scanf("%d %d", &l, &r);
      sort(dat.begin() + l, dat.begin() + r);
      reverse(dat.begin() + l, dat.begin() + r);
    }
  }
  return 0;
}
