#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  int N = inf.readInt(1, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(1, Q_MAX);
  inf.readChar('\n');

  for(int i = 0; i < N; i++) {
    char c = inf.readChar();
    if (c != '0' && c != '1') exit(1);
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    inf.readInt(1, 5);
    inf.readSpace();
    inf.readInt(0, N - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
