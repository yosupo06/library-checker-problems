#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#include "stirling_number_query.hpp"

int main() {
  int T, p;
  scanf("%d %d\n", &T, &p);

  Stirling_Number_Query X(p, 0, 1);

  for (int t = 0; t < T; ++t) {
    long long n, k;
    scanf("%lld %lld\n", &n, &k);
    int ans = X.S2(n, k);
    printf("%d\n", ans);
  }
  return 0;
}
