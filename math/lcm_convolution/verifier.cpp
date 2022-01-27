#include <iostream>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();
  int n = inf.readInt(1, N_MAX);
  inf.readEoln();

  for (int i = 1; i <= n; i++) {
    if (i > 1) inf.readSpace();
    inf.readInt(0, MOD - 1);
  }
  inf.readEoln();

  for (int i = 1; i <= n; i++) {
    if (i > 1) inf.readSpace();
    inf.readInt(0, MOD - 1);
  }
  inf.readEoln();

  inf.readEof();
  return 0;
}
