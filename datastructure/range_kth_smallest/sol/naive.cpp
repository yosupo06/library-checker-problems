#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (int &e : a)
    scanf("%d", &e);
  for (int i = 0; i != q; i += 1) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    std::vector<int> b(a.begin() + l, a.begin() + r);
    std::nth_element(b.begin(), b.begin() + k, b.end());
    printf("%d\n", b[k]);
  }
}