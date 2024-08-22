#include <cstdio>
#include "../params.h"
#include "common.hpp"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform(PROD_N_MAX - 1000, PROD_N_MAX);
  vector<int> ns = {N};
  int k = 1;

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
