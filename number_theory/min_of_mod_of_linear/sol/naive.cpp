#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    ll N, M, A, B;
    scanf("%lld %lld %lld %lld", &N, &M, &A, &B);
    ll ANS = M;
    for (int x = 0; x < N; ++x) {
      ll y = (A * x + B) % M;
      ANS = min(ANS, y);
    }
    printf("%lld\n", ANS);
  }
  return 0;
}
