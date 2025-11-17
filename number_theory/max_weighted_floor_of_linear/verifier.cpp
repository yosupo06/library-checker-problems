#include <iostream>

#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  int t = inf.readInt(T_MIN, T_MAX);
  inf.readChar('\n');
  for (int i = 0; i < t; i++) {
    inf.readLong(NM_MIN, NM_MAX);
    inf.readSpace();
    long long M = inf.readLong(NM_MIN, NM_MAX);
    inf.readSpace();
    inf.readLong(AB_MIN, AB_MAX);
    inf.readSpace();
    inf.readLong(AB_MIN, AB_MAX);
    inf.readSpace();
    inf.readLong(0, M - 1);
    inf.readSpace();
    inf.readLong(0, M - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
