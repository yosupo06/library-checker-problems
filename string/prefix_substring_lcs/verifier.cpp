#include <locale>
#include <string>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  const std::string S = inf.readToken();
  inf.readChar('\n');
  const int M = S.size();
  ensure(M_MIN <= M && M <= M_MAX);
  for (const char c : S) {
    ensure(std::islower(c));
  }

  const std::string T = inf.readToken();
  inf.readChar('\n');
  const int N = T.size();
  ensure(N_MIN <= N && N <= N_MAX);
  for (const char c : T) {
    ensure(std::islower(c));
  }

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
