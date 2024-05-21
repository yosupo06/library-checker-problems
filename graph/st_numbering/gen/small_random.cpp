#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

const int case_n_max = 15;
const int case_m_max = 100;

// shuffle and output
void print_case(Random& gen, int N, vector<pair<int, int>> G, int a, int b) {
  gen.shuffle(G.begin(), G.end());
  for (auto& [a, b]: G) {
    if (gen.uniform<int>(0, 1)) swap(a, b);
  }
  vector<int> new_idx(N);
  for (int i = 0; i < N; ++i) new_idx[i] = i;
  gen.shuffle(new_idx.begin(), new_idx.end());
  a = new_idx[a], b = new_idx[b];
  for (auto& [a, b]: G) a = new_idx[a], b = new_idx[b];

  int M = G.size();
  printf("%d %d %d %d\n", N, M, a, b);
  for (auto& [a, b]: G) printf("%d %d\n", a, b);
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<pair<int, int>> NM;
  int n_sum = 0, m_sum = 0;
  int t = 0;

  while (t < T_MAX && n_sum < N_MAX && m_sum < M_MAX) {
    int n = gen.uniform<int>(2, case_n_max);
    int m = gen.uniform<int>(0, case_m_max);
    n = min<int>(n, N_MAX - n_sum);
    m = min<int>(m, M_MAX - m_sum);
    if (n == 1) break;

    NM.emplace_back(n, m);
    n_sum += n, m_sum += m, t += 1;
  }

  printf("%d\n", t);
  for (auto& [n, m]: NM) {
    vector<pair<int, int>> G;
    for (int i = 0; i < m; ++i) {
      G.emplace_back(gen.uniform_pair<int>(0, n - 1));
    }
    print_case(gen, n, G, 0, 1);
  }
  return 0;
}
