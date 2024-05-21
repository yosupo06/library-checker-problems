#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

const int case_n_max = 1000;
const int case_m_max = 5000;

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

void print_case_from_NM(Random& gen, int n, int m) {
  /*
  関節点 a を選ぶ.
  集合 L, R を選ぶ.
  辺は L+a または R+a の間だけで結ぶようにする
  L+a から s, t を選ぶ
  */
  assert(n >= 3);
  int k = gen.uniform<int>(1, n - 2);
  vector<int> L, R;
  for (int i = 1; i < 1 + k; ++i) L.emplace_back(i);
  for (int i = 1 + k; i < n; ++i) R.emplace_back(i);
  assert(!L.empty());
  assert(!R.empty());

  auto [s, t] = gen.uniform_pair<int>(0, k);
  {
    int rnd = gen.uniform<int>(0, 2);
    if (rnd == 1 && s != 0 && t != 0) s = 0;
    if (rnd == 2 && s != 0 && t != 0) t = 0;
  }

  L.emplace_back(0);
  R.emplace_back(0);
  vector<pair<int, int>> G;

  auto get = [&](vector<int>& A) -> pair<int, int> {
    auto [a, b] = gen.uniform_pair<int>(0, int(A.size()) - 1);
    return {A[a], A[b]};
  };

  for (int i = 0; i < m; ++i) {
    int t = gen.uniform<int>(0, 1);
    if (t == 0) { G.emplace_back(get(L)); }
    if (t == 1) { G.emplace_back(get(R)); }
  }
  print_case(gen, n, G, s, t);
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<pair<int, int>> NM;
  int n_sum = 0, m_sum = 0;
  int t = 0;

  while (t < T_MAX && n_sum < N_MAX && m_sum < M_MAX) {
    int n = gen.uniform<int>(3, case_n_max);
    int m = gen.uniform<int>(0, case_m_max);
    n = min<int>(n, N_MAX - n_sum);
    m = min<int>(m, M_MAX - m_sum);
    if (n <= 2) break;

    NM.emplace_back(n, m);
    n_sum += n, m_sum += m, t += 1;
  }

  printf("%d\n", t);
  for (auto& [n, m]: NM) { print_case_from_NM(gen, n, m); }
  return 0;
}
