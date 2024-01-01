#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

const int case_n_max = 1000;
const int case_m_max = 5000;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<pair<int, int>> out;
  int n_sum = 0, m_sum = 0;
  int t = 0;

  while (t < T_MAX && n_sum < N_MAX && m_sum < M_MAX) {
    int n = gen.uniform<int>(1, case_n_max);
    int m = gen.uniform<int>(0, case_m_max);
    n = min<int>(n, N_MAX - n_sum);
    m = min<int>(m, M_MAX - m_sum);
    n_sum += n, m_sum += m, t += 1;
    vector<pair<int, int>> edges;
    int v = gen.uniform<int>(0, n - 1);
    for (int i = 0; i < m; ++i) {
      int w = gen.uniform<int>(0, n - 1);
      int a = v, b = w;
      if (gen.uniform<int>(0, 1)) swap(a, b);
      edges.emplace_back(a, b);
      v = w;
    }
    gen.shuffle(edges.begin(), edges.end());
    out.emplace_back(n, m);
    for (auto& [a, b]: edges) out.emplace_back(a, b);
  }

  printf("%d\n", t);
  for (auto [a, b]: out) printf("%d %d\n", a, b);
  return 0;
}
