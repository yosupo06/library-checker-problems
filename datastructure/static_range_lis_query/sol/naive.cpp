#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> P(N);
  for (int &p : P) {
    std::cin >> p;
  }

  const auto LIS = [N](const std::vector<int> &P) -> int {
    std::vector<int> dp(P.size(), N);
    for (const int p : P) {
      *std::lower_bound(dp.begin(), dp.end(), p) = p;
    }
    return std::lower_bound(dp.begin(), dp.end(), N) - dp.begin();
  };

  for (int i = 0; i < Q; i++) {
    int l, r;
    std::cin >> l >> r;
    std::cout << LIS({P.begin() + l, P.begin() + r}) << "\n";
  }

  return 0;
}
