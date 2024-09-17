#include <bitset>
#include <vector>
#include "random.h"

using namespace std;
using BS = bitset<4096>;

void out(int n, int m, vector<BS> A, BS b) {
  auto out_BS = [&](int n, BS x) -> void {
    string S(n, '?');
    for (int i = 0; i < n; ++i) S[i] = (x[i] ? '1' : '0');
    printf("%s\n", S.c_str());
  };
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) out_BS(m, A[i]);
  out_BS(n, b);
}

void gen_yes(int n, int m, int r, Random &gen) {
  assert(r <= m && r <= n);
  vector<BS> a(n);
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < m; ++j) { a[i][j] = gen.uniform_bool(); }
  }
  for (int i = r; i < n; ++i) {
    for (int k = 0; k < r; ++k) {
      if (gen.uniform_bool()) a[i] ^= a[k];
    }
  }
  BS x;
  for (int i = 0; i < m; ++i) x[i] = gen.uniform_bool();
  BS y;
  for (int i = 0; i < n; ++i) { y[i] = (a[i] & x).count() % 2; }
  out(n, m, a, y);
}

void gen_no(int n, int m, int r, Random &gen) {
  assert(r <= m && r < n);
  vector<BS> a(n);
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < m; ++j) { a[i][j] = gen.uniform_bool(); }
  }

  BS y;
  for (int i = 0; i < n; ++i) { y[i] = gen.uniform_bool(); }
  // at least one 1
  y[gen.uniform<int>(r, n - 1)] = 1;

  for (int i = r; i < n; ++i) {
    for (int k = 0; k < r; ++k) {
      if (gen.uniform_bool()) {
        a[i] ^= a[k];
        y[i] = y[i] ^ y[k];
      }
    }
  }
  out(n, m, a, y);
}
