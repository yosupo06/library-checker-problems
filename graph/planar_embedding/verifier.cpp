#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>
#include "testlib.h"
#include "params.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int t = inf.readInt(T_MIN, T_MAX, "T");
  inf.readChar('\n');

  int64_t n_sum = 0, m_sum = 0;
  for (int tc = 0; tc < t; tc++) {
    int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int m = inf.readInt(M_MIN, M_MAX, "M");
    inf.readChar('\n');
    n_sum += n;
    m_sum += m;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
      int a = inf.readInt(0, n - 1, "a_i");
      inf.readSpace();
      int b = inf.readInt(0, n - 1, "b_i");
      inf.readChar('\n');
      ensuref(a != b, "case %d: self-loop at vertex %d (edge %d)", tc, a, i);
      edges[i] = {min(a, b), max(a, b)};
    }
    sort(edges.begin(), edges.end());
    for (int i = 1; i < m; i++) {
      ensuref(edges[i - 1] != edges[i], "case %d: duplicate edge between %d and %d",
              tc, edges[i].first, edges[i].second);
    }
  }
  inf.readEof();

  ensuref(n_sum <= N_MAX, "sum of N exceeds N_MAX");
  ensuref(m_sum <= M_MAX, "sum of M exceeds M_MAX");
  return 0;
}
