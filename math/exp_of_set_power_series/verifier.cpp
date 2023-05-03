#include "testlib.h"

#include "params.h"

int main() {
  registerValidation();

  const int N = inf.readInt(0, N_MAX);
  inf.readChar('\n');

  inf.readInt(0, 0);
  for (int i = 1; i < 1 << N; i++) {
    inf.readChar(' ');
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  inf.readEof();

  return 0;
}
