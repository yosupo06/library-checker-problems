#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();

  int T = inf.readInt(1, T_MAX);
  inf.readChar('\n');

  long long SUM_N = 0;
  for (int t = 0; t < T; ++t) {
    int n = inf.readInt(0, SUM_N_MAX);
    SUM_N += n;
    inf.readChar('\n');
    for (int i = 0; i < n; i++) {
      inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
      inf.readSpace();
      inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
      inf.readChar('\n');
    }
  }
  inf.readEof();

  ensure(SUM_N <= SUM_N_MAX);

  return 0;
}
