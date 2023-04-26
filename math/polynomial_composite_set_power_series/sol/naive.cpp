#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

using ll = long long;
constexpr int mod = 998244353;

int main() {
  int M, N;
  scanf("%d%d", &M, &N);

  std::vector<ll> f(M), s(1 << N), h(1 << N);
  for (auto &e : f)
    scanf("%lld", &e);
  for (auto &e : s)
    scanf("%lld", &e);
  std::reverse(f.begin(), f.end());
  for (const ll &a : f) {
    std::vector<ll> p(1 << N);
    // p <- s * h
    for (int i = 0; i < 1 << N; i++) {
      for (int j = i; j != -1; j--) {
        j &= i;
        p[i] = (p[i] + s[j] * h[i - j]) % mod;
      }
    }
    // h <- p + a
    h = p;
    h[0] = (h[0] + a) % mod;
  }

  for (int i = 0; i < 1 << N; i++) {
    printf("%lld%c", h[i], " \n"[i + 1 == 1 << N]);
  }

  return 0;
}
