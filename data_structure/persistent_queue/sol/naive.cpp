#include <cstdio>
#include <queue>
#include <vector>

int main() {
  int q;
  std::scanf("%d", &q);

  std::vector<std::queue<int>> s_(q + 1);
  const auto s = s_.begin() + 1;

  for (int i = 0; i != q; i += 1) {
    int c;
    std::scanf("%d", &c);
    switch (c) {
    case 0: {
      int t, x;
      std::scanf("%d%d", &t, &x);
      s[i] = s[t];
      s[i].push(x);
    } break;
    case 1: {
      int t;
      std::scanf("%d", &t);
      s[i] = s[t];
      std::printf("%d\n", s[i].front());
      s[i].pop();
    } break;
    }
  }
}
