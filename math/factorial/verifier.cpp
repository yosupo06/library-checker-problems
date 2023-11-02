#include <iostream>
#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();
  inf.readLong(0, MOD - 1);
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
