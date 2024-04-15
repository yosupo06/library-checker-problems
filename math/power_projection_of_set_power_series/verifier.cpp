#include "testlib.h"

#include "params.h"

int main() {
  registerValidation();

  const int N = inf.readInt(0, N_MAX);
  inf.readChar(' ');
  inf.readInt(0, M_MAX);
  inf.readChar('\n');

  for (int i = 0; i < 1 << N; i++) {
    if (i) inf.readChar(' ');
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  for (int i = 0; i < 1 << N; i++) {
    if (i) inf.readChar(' ');
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  inf.readEof();

  return 0;
}
