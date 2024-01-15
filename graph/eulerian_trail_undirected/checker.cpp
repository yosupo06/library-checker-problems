#include <algorithm>
#include <vector>
#include <utility>
#include "testlib.h"

using namespace std;

// -1: invalid, 0: No, 1: Yes
int read_ans(int N, int M, vector<pair<int, int>> edge, InStream& stream) {
  string YN = stream.readToken();
  if (YN == "No") return 0;
  if (YN != "Yes") return -1;

  vector<int> vs(M + 1), es(M);
  for (int i = 0; i < M + 1; ++i) vs[i] = stream.readInt(0, N - 1);
  for (int i = 0; i < M; ++i) es[i] = stream.readInt(0, M - 1);

  // es[i] connect vs[i] and vs[i+1]
  for (int i = 0; i < M; ++i) {
    auto [a, b] = edge[es[i]];
    if (vs[i] == a && vs[i + 1] == b) continue;
    if (vs[i] == b && vs[i + 1] == a) continue;
    return -1;
  }

  // es is permtation
  sort(es.begin(), es.end());
  for (int i = 0; i < M; ++i) {
    if (es[i] != i) return -1;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();
  for (int t = 0; t < T; ++t) {
    int N = inf.readInt();
    int M = inf.readInt();
    vector<pair<int, int>> edge;
    for (int m = 0; m < M; ++m) {
      int a = inf.readInt();
      int b = inf.readInt();
      edge.emplace_back(a, b);
    }
    int OUF = read_ans(N, M, edge, ouf);
    int ANS = read_ans(N, M, edge, ans);
    if (ANS == -1) {
      quitf(_fail, "writer's output is invalid in testcase %d", t);
    }
    if (OUF == -1) { quitf(_wa, "output is invalid in testcase %d", t); }
    if (ANS == OUF) continue;
    if (ANS == 0 && OUF == 1) {
      quitf(_fail,
            "in testcase %d, perticipant find a trail, but writer don't.", t);
    }
    if (ANS == 1 && OUF == 0) {
      quitf(_wa, "in testcase %d, writer find a trail, but perticipant don't.",
            t);
    }
  }
  quitf(_ok, "OK");
}
