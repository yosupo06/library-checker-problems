#include <cstdio>
#include <cstdlib>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  int N = inf.readInt(MIN_N, MAX_N);
  inf.readSpace();
  int Q = inf.readInt(MIN_Q, MAX_Q);
  inf.readChar('\n');

  for (int i = 0; i < N; ++i) {
    if (i) inf.readSpace();
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    int k = inf.readInt(0, N);
    inf.readSpace();
    inf.readInt(0, N - k);
    inf.readSpace();
    inf.readInt(0, N - k);
    inf.readChar('\n');
  }

  inf.readEof();
  return 0;
}
