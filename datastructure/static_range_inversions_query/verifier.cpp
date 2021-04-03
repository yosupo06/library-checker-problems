#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readChar(' ');
  int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i != N; ++i) {
    if (i != 0) {
      inf.readChar(' ');
    }
    inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');

  for (int i = 0; i != Q; ++i) {
    int l = inf.readInt(0, N);
    inf.readChar(' ');
    inf.readInt(l + 1, N);
    inf.readChar('\n');
  }

  inf.readEof();
  return 0;
}
