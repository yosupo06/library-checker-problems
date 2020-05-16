#include "testlib.h"

struct Result {
  int X;
  long long Y;
  std::vector<int> path;
};

int main(int argc, char *argv[]) {

  registerTestlibCmd(argc, argv);

  int n = readInt();

  using edge = std::pair<int, int>;
  std::map<edge, long long> edges;
  for (int i = 0; i < n - 1; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    long long c = inf.readInt();
    if (a > b) {
      swap(a, b);
    }
    
    edges[make_pair(a, b)] = c;
  }
  
  Result res_ans;
  Result res_submitted;


  res_ans.X = ans.readInt();
  res_ans.Y = ans.readInt();

  res_submitted.X = ouf.readLong();
  res_submitted.Y = ouf.readLong();

  // 木の直径が正しいことの確認
  if (res_ans.Y != res_submitted.Y) {
    quitf(_wa, "Tree Diameter is differ - expected: '%lld', found '%d'", res_ans.Y, res_submitted.Y);
  }


  // 復元されたパスが，ちゃんと正しいかを確認
  for (int i = 0; i < res_ans.X; i++) {
    int node = ouf.readInt();
    res_submitted.path.push_back(node);
  }

  int cur = res_submitted.path[0];
  long long cost;
  std::vector<bool> visited(n, false);
  visited[cur] = true;
  for (int i = 1; i < res_submitted.path.size(); i++) {
    int u = res_submitted.path[i - 1];
    int v = res_submitted.path[i];
    if (u > v) {
      swap(u, v);
    }

    // 存在する？
    if (edges.find({u, v}) == edges.end()) {
      quitf(_wa, "using an edge that doesn't exist : (%d, %d)", u, v);
    }

    // 片方は cur?
    if (cur == v) {
      cur = u;
    } else if (cur == u) {
      cur = v;
    } else {
      quitf(_wa, "teleporting from vertex %d to vertex %d or %d", cur, u, v);
    }

    // 同じ頂点は二度訪れてはいけない
    if (visited[cur]) {
      quitf(_wa, "visited the same vertex #%d twice", cur);
    }

    cost += edge({u, v});
  }

  // cost は Y と一致する？
  if (cost != Y) {
    quitf(_wa, "total weights differ between Y(" %lld ") and submitted path's(" %lld ")", Y, cost);
  }

  if (ouf.seekEof()) {
    quitf(_ok, "OK");
  } else {
    quitf(_ng, "unexpected token");
  }
  
  return 0;
}
