#include <algorithm>
#include <vector>
#include <utility>
#include "testlib.h"

using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();

  for (int t = 0; t < T; ++t) {
    int N = inf.readInt();
    vector<ll> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
      X[i] = inf.readInt();
      Y[i] = inf.readInt();
    }

    int a = ans.readInt(0, N - 1);
    int b = ans.readInt(0, N - 1);
    int c = ouf.readInt(0, N - 1);
    int d = ouf.readInt(0, N - 1);

    if (c == d) { quitf(_wa, "output same index in testcase %d", t); }

    auto dist = [&](int i, int j) -> ll {
      ll dx = X[i] - X[j], dy = Y[i] - Y[j];
      return dx * dx + dy * dy; // at most 8*10^{18}
    };

    ll x = dist(a, b);
    ll y = dist(c, d);

    if (x == y) continue;
    if (x > y) { quitf(_wa, "the distance is not optimal in testcase %d", t); }
    if (x < y) {
      quitf(_fail, "the distance of writer is smaller in testcase %d", t);
    }
  }
  quitf(_ok, "OK");
}
