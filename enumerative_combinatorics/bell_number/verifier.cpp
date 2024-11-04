#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  inf.readInt(0, N_MAX);
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
