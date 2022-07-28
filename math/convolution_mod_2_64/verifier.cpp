#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  const int N = inf.readInt(1, N_AND_M_MAX);
  inf.readChar(' ');
  const int M = inf.readInt(1, N_AND_M_MAX);
  inf.readChar('\n');
  for (int i = 0; i < N; ++i) {
    if (i > 0) inf.readChar(' ');
    inf.readUnsignedLong();
  }
  inf.readChar('\n');
  for (int i = 0; i < M; ++i) {
    if (i > 0) inf.readChar(' ');
    inf.readUnsignedLong();
  }
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
