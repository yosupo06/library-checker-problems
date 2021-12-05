#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  int M, N, Q;
  std::scanf("%d%d%d", &M, &N, &Q);
  std::string S(M, ' '), T(N, ' ');
  std::scanf("%*c");
  for (char &c : S) {
    std::scanf("%c", &c);
  }
  std::scanf("%*c");
  for (char &c : T) {
    std::scanf("%c", &c);
  }

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
    std::scanf("%d%d%d", &a, &b, &c);
    std::printf("%d\n", lcs[a][b][c]);
  }

  return 0;
}
