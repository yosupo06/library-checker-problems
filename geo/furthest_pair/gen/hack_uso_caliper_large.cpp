#include <cstdio>
#include <cstdlib>
#include <utility>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

using P = pair<ll, ll>;

ll f(ll R, ll x) {
  // floor(sqrt(R^2-x^2))
  long long ok = 0, ng = R + 1;
  while (ok + 1 < ng) {
    long long mi = (ok + ng) / 2;
    (x * x + mi * mi <= R * R ? ok : ng) = mi;
  }
  return ok;
}

void out(vector<vector<P>> ALL) {
  int T = ALL.size();
  printf("%d\n", T);
  for (auto& S: ALL) {
    int n = S.size();
    printf("%d\n", n);
    for (auto& [x, y]: S) { printf("%lld %lld\n", x, y); }
  }
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<vector<P>> ALL;
  ll R = X_AND_Y_ABS_MAX / 10;
  ll n = SUM_N_MAX / 2;

  auto make_half = [&]() -> vector<P> {
    // y>0
    vector<P> A;
    ll x0, y0, x1, y1, x2, y2;
    while (1) {
      x0 = -R, y0 = 0;
      x1 = gen.uniform<ll>(-R + 1, 0);
      y1 = f(R, x1);
      tie(x2, y2) = [&]() -> P {
        for (ll x = x1 + 1; x < x1 + 100; ++x) {
          ll y = y1 * (x + R) / (x1 + R);
          ll a = R - x1, b = y1;
          ll c = R - x, d = y;
          if (a * a + b * b >= c * c + d * d) continue;
          return {x, y};
        }
        return {-1, -1};
      }();
      if (x2 == -1) continue;
      break;
    }
    A.emplace_back(x0, y0);
    A.emplace_back(x1, y1);
    A.emplace_back(x2, y2);
    for (int i = 0; i < n - 3; ++i) {
      while (1) {
        ll x = gen.uniform<ll>(x2 + 1, R);
        ll y = gen.uniform<ll>(0, y2);
        if (10 * (x * x + y * y) <= R * R * 9) {
          A.emplace_back(x, y);
          break;
        }
      }
    }
    return A;
  };

  vector<P> A = make_half();
  vector<P> B = make_half();
  for (auto& [a, b]: B) a = -a, b = -b;
  A.insert(A.end(), B.begin(), B.end());
  gen.shuffle(A.begin(), A.end());

  // ランダムな相似変換をしたい
  if (gen.uniform<int>(0, 1)) {
    for (auto& [a, b]: A) swap(a, b);
  }
  auto [a, b] = [&]() -> pair<ll, ll> {
    while (1) {
      ll a = gen.uniform<int>(-3, 3);
      ll b = gen.uniform<int>(-3, 3);
      if (a == 0 && b == 0) continue;
      if (a * a + b * b > 10) continue;
      return {a, b};
    }
  }();
  // z -> (a+bi)z
  for (auto& [x, y]: A) tie(x, y) = make_pair(a * x - b * y, a * y + b * x);
  ALL.emplace_back(A);

  out(ALL);
  return 0;
}
