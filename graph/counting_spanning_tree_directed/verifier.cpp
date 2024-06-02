#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int M = inf.readInt(M_MIN, M_MAX);
  inf.readSpace();
  inf.readInt(0, N - 1); // r
  inf.readChar('\n');

  for (int i = 0; i < M; i++) {
    inf.readInt(0, N - 1);
    inf.readSpace();
    inf.readInt(0, N - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
