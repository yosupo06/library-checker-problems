#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  const int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i < N; i++) {
    if (i != 0) { inf.readSpace(); }
    inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    int t = inf.readInt(0, 1);
    inf.readSpace();
    if (t == 0) {
      inf.readInt(0, N);
      inf.readSpace();
      inf.readInt(A_MIN, A_MAX);
      inf.readChar('\n');
    }
    if (t == 1) {
      const int l = inf.readInt(0, N);
      inf.readSpace();
      inf.readInt(l, N);
      inf.readSpace();
      inf.readInt(A_MIN, A_MAX);
      inf.readChar('\n');
    }
  }

  inf.readEof();

  return 0;
}
