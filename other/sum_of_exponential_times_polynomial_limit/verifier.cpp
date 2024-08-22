#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  const long long R = inf.readLong(0, MOD - 1, "R");
  inf.readChar(' ');
  inf.readInt(D_MIN, D_MAX, "D");
  inf.readChar('\n');
  inf.readEof();

  ensuref(R != 1, "R != 1 must hold");
  return 0;
}
