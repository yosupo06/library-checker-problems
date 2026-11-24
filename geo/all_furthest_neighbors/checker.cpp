#include <vector>

#include "testlib.h"

using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();
  for (int t = 0; t < T; ++t) {
    int n = inf.readInt();
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; ++i) {
      x[i] = inf.readLong();
      y[i] = inf.readLong();
    }

    auto dist = [&](int i, int j) -> ll {
      ll dx = x[i] - x[j];
      ll dy = y[i] - y[j];
      return dx * dx + dy * dy;
    };

    for (int i = 0; i < n; ++i) {
      int expected = ans.readInt(0, n - 1);
      int actual = ouf.readInt(0, n - 1);
      ll expected_dist = dist(i, expected);
      ll actual_dist = dist(i, actual);
      if (actual_dist < expected_dist) {
        quitf(_wa, "the answer for vertex %d is not optimal in testcase %d",
              i, t);
      }
      if (actual_dist > expected_dist) {
        quitf(_fail,
              "the jury answer for vertex %d is not optimal in testcase %d",
              i, t);
      }
    }
  }
  if (!ouf.seekEof()) quitf(_wa, "participant output contains extra tokens");
  quitf(_ok, "OK");
}
