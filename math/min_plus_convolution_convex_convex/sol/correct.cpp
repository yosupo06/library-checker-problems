#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
using vc = vector<T>;

// select(i,j,k) : (i,j) -> (i,k)
template <typename F>
vc<int> monotone_minima(int H, int W, F select) {
  vc<int> min_col(H);
  auto dfs = [&](auto& dfs, int x1, int x2, int y1, int y2) -> void {
    if (x1 == x2) return;
    int x = (x1 + x2) / 2;
    int best_y = y1;
    for (int y = y1 + 1; y < y2; ++y) {
      if (select(x, best_y, y)) best_y = y;
    }
    min_col[x] = best_y;
    dfs(dfs, x1, x, y1, best_y + 1);
    dfs(dfs, x + 1, x2, best_y, y2);
  };
  dfs(dfs, 0, H, 0, W);
  return min_col;
}

vc<int> min_plus_convolution(vc<int> A, vc<int> B) {
  int N = A.size(), M = B.size();
  // B is convex
  for (int i = 0; i < M - 2; ++i) assert(B[i] + B[i + 2] >= 2 * B[i + 1]);
  auto select = [&](int i, int j, int k) -> bool {
    if (i < k) return false;
    if (i - j >= M) return true;
    return A[j] + B[i - j] >= A[k] + B[i - k];
  };
  vc<int> J = monotone_minima(N + M - 1, N, select);
  vc<int> C(N + M - 1);
  for (int i = 0; i < N + M - 1; ++i) {
    int j = J[i];
    C[i] = A[j] + B[i - j];
  }
  return C;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vc<int> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  vc<int> c = min_plus_convolution(a, b);
  for (int i = 0; i < n + m - 1; i++) {
    if (i) printf(" ");
    printf("%d", c[i]);
  }
  printf("\n");
  return 0;
}
