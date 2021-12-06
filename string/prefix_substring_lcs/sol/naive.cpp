#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int Q;
  std::string S, T;
  std::cin >> Q >> S >> T;
  const int M = S.size();
  const int N = T.size();

  auto lcs = std::vector(M + 1, std::vector(N + 1, std::vector(N + 1, int(0))));
  for (int a = 1; a <= M; a++) {
    for (int b = 0; b <= N; b++) {
      for (int c = b + 1; c <= N; c++) {
        if (S[a - 1] == T[c - 1]) {
          lcs[a][b][c] = lcs[a - 1][b][c - 1] + 1;
        } else {
          lcs[a][b][c] = std::max(lcs[a - 1][b][c], lcs[a][b][c - 1]);
        }
      }
    }
  }

  for (int i = 0; i < Q; i++) {
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << lcs[a][b][c] << "\n";
  }

  return 0;
}
