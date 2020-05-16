#include <iostream>
#include "testlib.h"

struct Result {
  long long X;
  int Y;
  std::vector<int> path;
};

int main(int argc, char *argv[]) {

  registerTestlibCmd(argc, argv);

  int N = inf.readInt();

  using edge = std::pair<int, int>;
  std::map<edge, long long> edges;
  for (int i = 0; i < N - 1; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    long long c = inf.readInt();
    if (a > b) {
      std::swap(a, b);
    }
    
    edges[std::make_pair(a, b)] = c;
  }
  
  
  Result res_ans;
  Result res_submitted;

  res_ans.X = ans.readLong();
  res_ans.Y = ans.readInt();

  res_submitted.X = ouf.readLong();
  res_submitted.Y = ouf.readInt();

  // 木の直径が正しいことの確認
  if (res_ans.X != res_submitted.X) {
    quitf(_wa, "Tree Diameter is differ - expected: '%d', found '%d'", res_ans.Y, res_submitted.Y);
  }

  // 復元されたパスが，ちゃんと正しいかを確認
  for (int i = 0; i < res_ans.Y; i++) {
    int node = ouf.readInt();
    res_submitted.path.push_back(node);
  }

  int cur = res_submitted.path[0];
  long long cost = 0;
  std::vector<bool> visited(N, false);
  visited[cur] = true;

  for (size_t i = 1; i < res_submitted.path.size(); i++) {
    int u = res_submitted.path[i - 1];
    int v = res_submitted.path[i];
    if (u > v) {
      std::swap(u, v);
    }

    // 存在する？
    if (edges.find({u, v}) == edges.end()) {
      quitf(_wa, "using an edge that doesn't exist : (%d, %d)", u, v);
    }

    // パスが繋がってるかを確認
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

    visited[cur] = true;

    cost += edges[std::make_pair(u, v)];
  }

  // cost は X と一致する？
  if (cost != res_submitted.X) {
    quitf(_wa, "total weights differ between Y(%lld) and submitted path's(%lld)", res_submitted.X, cost);
  }

  if (ouf.seekEof()) {
    quitf(_ok, "OK");
  } else {
    quitf(_wa, "unexpected token");
  }
  
  return 0;
}
