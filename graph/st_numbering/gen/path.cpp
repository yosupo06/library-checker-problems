#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

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

  printf("1\n");

  int n = min(N_MAX, M_MAX + 1);
  vector<pair<int, int>> G;
  for (int i = 0; i < n - 1; ++i) G.emplace_back(i, i + 1);
  print_case(gen, n, G, 0, n - 1);
  return 0;
}
