#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <cassert>

#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;

using BS = bitset<4096>;

void gen_and_out(Random& gen, int n, int rk) {
  assert(0 <= rk && rk <= n);
  vector<int> col(n);
  for (int i = 0; i < n; ++i) { col[i] = i; }
  gen.shuffle(col.begin(), col.end());
  col.resize(rk);

  vector<BS> mat(n);
  for (int i = 0; i < rk; ++i) {
    int j = col[i];
    mat[i][j] = 1;
  }

  // apply random row operations
  gen.shuffle(mat.begin(), mat.end());
  for (int iter = 0; iter <= n * n; iter++) {
    auto [i, j] = gen.uniform_pair<int>(0, n - 1);
    if (gen.uniform<int>(0, 1)) { swap(i, j); }
    mat[i] ^= mat[j];
  }

  // output
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { printf("%d", 1 * mat[i][j]); }
    printf("\n");
  }
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int r = gen.uniform<int>(0, n);

  if (seed % 8 == 0) r = 0;
  if (seed % 8 == 1) r = 1;
  if (seed % 8 == 2) r = 2;
  if (seed % 8 == 3) r = n - 2;
  if (seed % 8 == 4) r = n - 1;
  gen_and_out(gen, n, r);
  return 0;
}
