#include <iostream>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();
  int n = inf.readInt(1, N_MAX);
  inf.readChar('\n');
  for (int i = 0; i < n; i++) {
    inf.readInt(0, MOD - 1);
    if (i != n - 1) inf.readSpace();
  }
  inf.readChar('\n');
  for (int i = 0; i < n; i++) {
    if (i)
      inf.readInt(0, MOD - 1);
    else
      inf.readInt(0, 0);
    if (i != n - 1) inf.readSpace();
  }
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
