#include <cstdio>
#include "../params.h"
#include "random.h"
#include "common.hpp"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<int> ns;
  int k = gen.uniform(1, 3);
  int N = 1;
  int MAX = 10;
  for (int i = 0; i < k; i++) {
    if (2 * N > MAX) break;
    int n = gen.uniform(2, MAX / N);
    ns.push_back(n);
    N *= n;
  }
  gen.shuffle(ns.begin(), ns.end());
  k = int(ns.size());

  int p = rand_prime(ns, gen);

  vector<int> f = rand_vec(ns, gen, p);
  vector<int> g = rand_vec(ns, gen, p);

  printf("%d %d\n", p, k);
  for (int i = 0; i < k; i++) {
    printf("%d", ns[i]);
    if (i != k - 1) printf(" ");
  }
  printf("\n");
  for (int i = 0; i < N; i++) {
    printf("%d", f[i]);
    if (i != N - 1) printf(" ");
  }
  printf("\n");
  for (int i = 0; i < N; i++) {
    printf("%d", g[i]);
    if (i != N - 1) printf(" ");
  }
  printf("\n");
  return 0;
}
