#include "testlib.h"
#include "params.h"
#include <vector>

using lint = long long int;

void dfs(const std::vector<std::vector<int>> &g, std::vector<bool> &visited, int cur, int nxt, bool &ret) {

  visited[cur] = true;
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    if (visited[nxt]) {
      // 閉路が存在
      ret = false;
      return;
    }
    dfs(g, visited, nxt, cur, ret);
  }
}

bool isTree(const std::vector<std::vector<int>> &g) {

  int n = g.size();
  std::vector<bool> visited(n, false);
  bool ret = true;
  dfs(g, visited, 0, -1, ret); // 閉路があったら，ret が false で帰ってくる
  
  // 全頂点に訪問してるか確認（連結性のチェック）
  for (auto flag : visited) {
    if (!flag) {
      ret = false;
      break;
    }
  }

  return ret;
}

int main() {

  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readChar('\n');

  std::vector<std::vector<int>> g(n);

  for(int i = 0; i < N; i++) {
    int a = inf.readInt(0, N - 1);
    inf.readSpace();
    int b = inf.readInt(0, N - 1);
    inf.readSpace();
    lint c = inf.readLong(C_MIN, C_MAX);

    g[a].push_back(b);
    g[b].push_back(a);

    if(i + 1 == N) inf.readChar('\n');
    else inf.readSpace();
  }

  // 連結であること
  ensure(isTree(g));
    
  inf.readEof();
  return 0;
}
