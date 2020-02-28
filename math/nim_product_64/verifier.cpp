#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  const int T = inf.readInt(T_MIN, T_MAX);
  inf.readChar('\n');
  for (int t = 0; t < T; ++t) {
    inf.readUnsignedLong();
    inf.readChar(' ');
    inf.readUnsignedLong();
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
