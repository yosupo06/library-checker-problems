#include "testlib.h"

#include "params.h"

int main() {
  registerValidation();

  const int N = inf.readInt(0, N_MAX);
  inf.readChar(' ');
  const int Q = inf.readInt(0, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i < N; i++) {
    if (i)
      inf.readChar(' ');
    inf.readInt(0, A_MAX); // a_i
  }
  inf.readChar('\n');

  for (int j = 0; j < Q; j++) {
    inf.readInt(0, 1); // t
    inf.readChar(' ');
    const int l = inf.readInt(0, N);
    inf.readChar(' ');
    inf.readInt(l, N); // r
    inf.readChar('\n');
  }

  inf.readEof();

  return 0;
}
