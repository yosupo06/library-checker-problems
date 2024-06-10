#include "testlib.h"
#include "params.h"

using ll = long long;

int main() {
  registerValidation();
  ll N = inf.readLong(N_MIN, N_MAX, "N");
  inf.readSpace();
  ll M = inf.readLong(M_MIN, M_MAX, "M");
  inf.readChar('\n');

  for (int m = 0; m < M; ++m) {
    inf.readLong(0LL, N - 1);
    inf.readSpace();
    inf.readLong(0LL, N - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
