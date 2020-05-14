#include "testlib.h"
#include "params.h"
#include <vector>

using lint = long long int;

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readChar('\n');

  std::vector<std::vector<std::pair<int, lint>>> g(n);

  for(int i = 0; i < N; i++) {
    int a = inf.readInt(0, N - 1);
    inf.readSpace();
    int b = inf.readInt(0, N - 1);
    inf.readSpace();
    lint c = inf.readLong(C_MIN, C_MAX);

    g[a].push_back({b, c});
    g[b].push_back({a, c});

    if(i + 1 == N) inf.readChar('\n');
    else inf.readSpace();
  }

  // TODO グラフが木であることの判定（閉路がなく，連結であること）
    
  inf.readEof();
  return 0;
}
