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

  /*
  k=4
    1   3   5   7
  0 - 2 - 4 - 6 - 8
  n=2k+1, m=3k
  */

  int k = min((N_MAX - 1) / 2, M_MAX / 3);
  int n = 2 * k + 1;
  vector<pair<int, int>> G;
  for (int i = 0; i < k; ++i) {
    G.emplace_back(2 * i + 0, 2 * i + 1);
    G.emplace_back(2 * i + 0, 2 * i + 2);
    G.emplace_back(2 * i + 1, 2 * i + 2);
  }
  print_case(gen, n, G, 0, 2 * k);
  return 0;
}
