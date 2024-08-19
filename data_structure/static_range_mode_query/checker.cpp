#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  int N = inf.readInt();
  int Q = inf.readInt();
  vector<int> A(N);
  for (int i = 0; i < N; ++i) A[i] = inf.readInt();

  vector<vector<int>> IDS;
  map<int, int> MP;
  for (int i = 0; i < N; ++i) {
    int x = A[i];
    if (!MP.count(x)) {
      MP[x] = IDS.size();
      IDS.emplace_back(vector<int>());
    }
    IDS[MP[x]].emplace_back(i);
  }

  auto get_freq = [&](int x, int l, int r) -> int {
    if (!MP.count(x)) return 0;
    vector<int>& I = IDS[MP[x]];
    return lower_bound(I.begin(), I.end(), r)
           - lower_bound(I.begin(), I.end(), l);
  };

  for (int q = 0; q < Q; ++q) {
    int l = inf.readInt(), r = inf.readInt();
    int ans_x = ans.readInt(), ans_freq = ans.readInt();
    int ouf_x = ouf.readInt(), ouf_freq = ouf.readInt();
    if (ans_freq != get_freq(ans_x, l, r)) {
      quitf(_fail, "in query %d, writer's freq is invalid", q);
    }
    if (ouf_freq != get_freq(ouf_x, l, r)) {
      quitf(_wa, "in query %d, the frequency is wrong.", q);
    }
    if (ans_freq < ouf_freq) {
      quitf(_fail, "in query %d, writer's freq is not optimal.", q);
    }
    if (ans_freq > ouf_freq) {
      quitf(_wa, "in query %d, the frequency is not optimal.", q);
    }
  }
  quitf(_ok, "OK");
}