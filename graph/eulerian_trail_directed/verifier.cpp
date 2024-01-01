#include "testlib.h"
#include "params.h"

using ll = long long;

int main() {
  registerValidation();

  ll T = inf.readLong(T_MIN, T_MAX);
  inf.readChar('\n');

  ll N_SUM = 0, M_SUM = 0;
  for (int t = 0; t < T; ++t) {
    ll N = inf.readLong(N_MIN, N_MAX, "N");
    inf.readSpace();
    ll M = inf.readLong(M_MIN, M_MAX, "M");
    inf.readChar('\n');

    N_SUM += N, M_SUM += M;
    for (int m = 0; m < M; ++m) {
      inf.readLong(0LL, N - 1);
      inf.readSpace();
      inf.readLong(0LL, N - 1);
      inf.readChar('\n');
    }
  }
  inf.readEof();

  ensure(N_SUM <= N_MAX && M_SUM <= M_MAX);
  return 0;
}
