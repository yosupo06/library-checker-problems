#include <algorithm>
#include <vector>
#include <utility>
#include "testlib.h"

using namespace std;

// -1: invalid, 0: No, 1: Yes
int read_ans(int N, vector<pair<int, int>> edge, InStream& stream, int s,
             int t) {
  string YN = stream.readToken();
  if (YN == "No") return 0;
  if (YN != "Yes") return -1;

  vector<int> p(N);
  for (int v = 0; v < N; ++v) p[v] = stream.readInt(0, N - 1);

  // sorted vertices
  vector<int> vs(N, -1);
  for (int v = 0; v < N; ++v) vs[p[v]] = v;

  // permutation?
  for (int i = 0; i < N; ++i)
    if (vs[i] == -1) return -1;

  // orient edges, make adj list
  vector<vector<int>> adj(N);
  for (auto& [a, b]: edge) {
    if (p[a] > p[b]) swap(a, b);
    adj[a].emplace_back(b);
  }

  // come from s
  vector<int> FROM(N);
  FROM[s] = 1;
  for (int i = 0; i < N; ++i) {
    int v = vs[i];
    if (!FROM[v]) return -1;
    for (auto& w: adj[v]) FROM[w] = 1;
  }
  // go to t
  vector<int> TO(N);
  TO[t] = 1;
  for (int i = N - 1; i >= 0; --i) {
    int v = vs[i];
    for (auto& w: adj[v]) TO[v] |= TO[w];
    if (!TO[v]) return -1;
  }

  return 1;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();
  for (int t = 0; t < T; ++t) {
    int N = inf.readInt();
    int M = inf.readInt();
    int a = inf.readInt();
    int b = inf.readInt();

    vector<pair<int, int>> edge;
    for (int m = 0; m < M; ++m) {
      int a = inf.readInt();
      int b = inf.readInt();
      edge.emplace_back(a, b);
    }

    int OUF = read_ans(N, edge, ouf, a, b);
    int ANS = read_ans(N, edge, ans, a, b);
    if (ANS == -1) {
      quitf(_fail, "writer's output is invalid in testcase %d", t);
    }
    if (OUF == -1) { quitf(_wa, "output is invalid in testcase %d", t); }
    if (ANS == OUF) continue;
    if (ANS == 0 && OUF == 1) {
      quitf(_fail,
            "in testcase %d, perticipant find a numbering, but writer don't.",
            t);
    }
    if (ANS == 1 && OUF == 0) {
      quitf(_wa,
            "in testcase %d, writer find a numbering, but perticipant don't.",
            t);
    }
  }
  quitf(_ok, "OK");
}
