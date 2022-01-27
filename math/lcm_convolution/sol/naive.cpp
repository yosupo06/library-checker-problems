#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;
using ll = long long;

constexpr int MOD = 998'244'353;

int lcm(int a, int b) {
  ll prod = ll(a) * ll(b);
  while (b) {
    a %= b;
    swap(a, b);
  }
  return prod / a;
}

int main() {
  int n;
  scanf("%d", &n);

  assert(n <= 1000);

  vector<ll> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);

  vector<ll> c(n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int k = lcm(i, j);
      if(k <= n){
        c[k] += a[i] * b[j];
        c[k] %= MOD;
      } 
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (i > 1) printf(" ");
    printf("%lld", c[i]);
  }
  printf("\n");

  return 0;
}
