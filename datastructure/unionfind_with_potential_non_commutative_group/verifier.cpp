#include "params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(1, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(1, Q_MAX);
  inf.readEoln();

  while(Q--) {
    int t = inf.readInt(0, 1);
    inf.readSpace();
    inf.readInt(0, N - 1);
    inf.readSpace();
    inf.readInt(0, N - 1);
    if (t == 0) {
      array<array<long long, 2>, 2> x;
      for(int i : {0, 1}) for(int j : {0, 1}) {
        inf.readSpace();
        x[i][j] = inf.readInt(0, MOD - 1);
      }
      ensuref((((x[0][0] * x[1][1] - x[0][1] * x[1][0]) % MOD) + MOD) % MOD == 1, "det(x) should be 1");
    }
    inf.readEoln();
  }

  inf.readEof();

  return 0;
}
