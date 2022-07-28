#include <iostream>

#include "./params.h"
#include "testlib.h"

int main() {
  registerValidation();

  int n = inf.readInt(1, N_MAX);
  inf.readSpace();
  int m = inf.readInt(1, N_MAX);
  inf.readSpace();
  int k = inf.readInt(1, N_MAX);
  inf.readChar('\n');

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      inf.readInt(0, MOD - 1);
      if (j + 1 != m) inf.readSpace();
    }
    inf.readChar('\n');
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      inf.readInt(0, MOD - 1);
      if (j + 1 != k) inf.readSpace();
    }
    inf.readChar('\n');
  }

  inf.readEof();
  return 0;
}
