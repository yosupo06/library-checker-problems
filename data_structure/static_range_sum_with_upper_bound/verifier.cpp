#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int N = inf.readInt(1, MAX_N_Q);
  inf.readSpace();
  const int Q = inf.readInt(1, MAX_N_Q);
  inf.readChar('\n');

  for (int i = 0; i < N; i++) {
    if (i != 0) {
      inf.readSpace();
    }
    inf.readInt(0, MAX_A_X);
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    const int l = inf.readInt(0, N);
    inf.readSpace();
    inf.readInt(l, N);
    inf.readSpace();
    inf.readInt(0, MAX_A_X);
    inf.readChar('\n');
  }

  inf.readEof();

  return 0;
}
