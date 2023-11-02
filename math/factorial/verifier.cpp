#include <iostream>
#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();
  int T = inf.readInt(1, T_MAX);
  inf.readChar('\n');
  for (int t = 0; t < T; ++t) {
    inf.readLong(0, MOD - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
