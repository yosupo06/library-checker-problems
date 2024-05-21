#include <algorithm>
#include <vector>
#include <utility>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();

  for (int t = 0; t < T; ++t) {
    vector<pair<int, int>> A, B;

    int M1 = ans.readInt();
    for (int i = 0; i < M1; ++i) {
      int x = ans.readInt();
      int y = ans.readInt();
      A.emplace_back(x, y);
    }

    int M2 = ouf.readInt(M1, M1);
    for (int i = 0; i < M2; ++i) {
      int x = ouf.readInt();
      int y = ouf.readInt();
      B.emplace_back(x, y);
    }

    rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
    rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

    if (A != B) { quitf(_wa, "wa in testcase %d", t); }
  }
  quitf(_ok, "OK");
}
