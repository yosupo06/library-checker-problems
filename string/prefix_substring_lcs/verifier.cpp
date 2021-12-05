#include <locale>
#include <string>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int M = inf.readInt(M_MIN, M_MAX);
  inf.readSpace();
  const int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  const int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i < M; i++) {
    const char c = inf.readChar();
    ensure(std::islower(c));
  }
  inf.readChar('\n');
  for (int i = 0; i < N; i++) {
    const char c = inf.readChar();
    ensure(std::islower(c));
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    inf.readInt(0, M);
    inf.readSpace();
    const int b = inf.readInt(0, N);
    inf.readSpace();
    inf.readInt(b, N);
    inf.readChar('\n');
  }

  inf.readEof();
  return 0;
}
