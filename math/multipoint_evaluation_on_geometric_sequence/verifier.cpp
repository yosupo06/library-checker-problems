#include <iostream>
#include <cassert>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();
  int N = inf.readInt(1, NM_MAX);
  inf.readSpace();
  inf.readInt(1, NM_MAX); // m
  inf.readSpace();
  inf.readInt(0, MOD - 1); // a
  inf.readSpace();
  inf.readInt(0, MOD - 1); // r
  inf.readChar('\n');

  for (int i = 0; i < N; ++i) {
    if (i) inf.readSpace();
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  inf.readEof();
  return 0;
}
