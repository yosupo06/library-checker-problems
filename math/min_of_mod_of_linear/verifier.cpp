#include <iostream>

#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  int t = inf.readInt(T_MIN, T_MAX);
  inf.readChar('\n');
  for (int i = 0; i < t; i++) {
    inf.readInt(NM_MIN, NM_MAX);
    inf.readSpace();
    int M = inf.readInt(NM_MIN, NM_MAX);
    inf.readSpace();
    inf.readInt(0, M - 1);
    inf.readSpace();
    inf.readInt(0, M - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
