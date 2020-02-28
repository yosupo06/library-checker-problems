#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int &e : a)
    std::cin >> e;
  for (int i = 0; i != q; i += 1) {
    int l, r, k;
    std::cin >> l >> r >> k;
    std::vector<int> b(a.begin() + l, a.begin() + r);
    std::nth_element(b.begin(), b.begin() + k, b.end());
    std::cout << b[k] << std::endl;
  }
}