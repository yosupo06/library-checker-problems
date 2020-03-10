#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  inf.readLong(0, MOD - 1, "R");
  inf.readChar(' ');
  inf.readInt(D_MIN, D_MAX, "D");
  inf.readChar(' ');
  inf.readLong(N_MIN, N_MAX, "N");
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
