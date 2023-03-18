#include "../params.h"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main(int, char**) {
  const int N = N_MAX;

  vector<pair<int, int>> edges;

  for (int k = 0; k < N / 3; k++) {
    edges.push_back({3 * k, 3 * k + 1});
    edges.push_back({3 * k + 1, 3 * k + 2});
    edges.push_back({3 * k + 2, 3 * k});
  }
  if (N % 3 == 1) {
    edges.push_back({N - 4, N - 1});
    edges.push_back({N - 3, N - 1});
    edges.push_back({N - 2, N - 1});
  }
  if (N % 3 == 2) {
    edges.push_back({N - 2, N - 1});
  }

  const int M = edges.size();

  printf("%d %d\n", N, M);
  for (int i = 0; i < M; i++) {
    printf("%d %d\n", edges[i].first, edges[i].second);
  }

  return 0;
}