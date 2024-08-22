#include <iostream>
#include "testlib.h"

struct Result {
  long long X;
  int Y;
  std::vector<int> path;
};
using edge = std::pair<int, int>;

// 出力を読む関数 
Result read_ans(int N, InStream &stream) {
  Result ret;
  ret.X = stream.readLong();
  ret.Y = stream.readInt(1, N);
  for (int i = 0; i < ret.Y; i++) {
    int node = stream.readInt(0, N - 1);
    ret.path.push_back(node);
  }

  return ret;
}

// チェックすること
// - 同じ頂点を二度踏まない
// - テレポートしない
// - 実際の距離が X と一致する
// - 辺が存在する
void validate_path(long long X, std::vector<int> path, int N, std::map<edge, long long> edges) {


  int cur = path[0]; // 現在の頂点
  long long cost = 0; // コストの総和
  std::vector<bool> visited(N, false); // 頂点の訪問済みフラグ
  visited[cur] = true;

  for (size_t i = 1; i < path.size(); i++) {
    int u = path[i - 1];
    int v = path[i];
    if (u > v) {
      std::swap(u, v);
    }

    // 存在する？
    if (edges.find(edge(u, v)) == edges.end()) {
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

    cost += edges[edge(u, v)];
  }

  // cost は X と一致する？
  if (cost != X) {
    quitf(_wa, "total weights differ between Y(" I64 ") and submitted path's(" I64 ")", X, cost);
  }
}

int main(int argc, char *argv[]) {

  registerTestlibCmd(argc, argv);

  // 入力受け取り
  int N = inf.readInt();

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

  // 出力受け取り
  Result res_ans = read_ans(N, ans);
  Result res_submitted = read_ans(N, ouf);

  // コンテスタントの出力した直径 X と，復元されたパスが正しいかを判定する
  validate_path(res_submitted.X, res_submitted.path, N, edges);

  // 木の直径が正しいことの確認
  if (res_ans.X > res_submitted.X) { 
    // 想定解より悪いとき
    quitf(_wa, "Tree Diameter is differ - expected: " I64 ", found " I64, res_ans.X, res_submitted.X);
  }
  if (res_ans.X < res_submitted.X) {
    // 想定解より良いとき
    quitf(_fail, "Contestant found the more optimal answer - expected: " I64 ", found " I64, res_ans.X, res_submitted.X);
  }

  quitf(_ok, "OK");
  
  return 0;
}
