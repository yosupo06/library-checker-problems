#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  int n=inf.readInt(K_MIN, N_MAX, "N");
  inf.readSpace();
  inf.readInt(K_MIN, n, "K");
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
