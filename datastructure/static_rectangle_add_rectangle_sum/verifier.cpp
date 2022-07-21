#include "testlib.h"
#include "params.h"

using ll = long long;

int main() {
  registerValidation();

  ll N = inf.readLong(N_MIN, N_MAX, "N");
  inf.readSpace();
  ll Q = inf.readLong(Q_MIN, Q_MAX, "Q");
  inf.readChar('\n');

  for (int n = 0; n < N; ++n) {
    ll l = inf.readLong(X_MIN, X_MAX, "l");
    inf.readSpace();
    ll d = inf.readLong(Y_MIN, Y_MAX, "d");
    inf.readSpace();
    ll r = inf.readLong(X_MIN, X_MAX, "r");
    inf.readSpace();
    ll u = inf.readLong(Y_MIN, Y_MAX, "u");
    inf.readSpace();
    inf.readLong(0, MOD - 1, "w");
    inf.readChar('\n');

    ensure(X_MIN <= l && l < r && r <= X_MAX);
    ensure(Y_MIN <= d && d < u && u <= Y_MAX);
  }

  for (int q = 0; q < Q; ++q) {
    ll l = inf.readLong(X_MIN, X_MAX, "l");
    inf.readSpace();
    ll d = inf.readLong(Y_MIN, Y_MAX, "d");
    inf.readSpace();
    ll r = inf.readLong(X_MIN, X_MAX, "r");
    inf.readSpace();
    ll u = inf.readLong(Y_MIN, Y_MAX, "u");
    inf.readChar('\n');

    ensure(X_MIN <= l && l < r && r <= X_MAX);
    ensure(Y_MIN <= d && d < u && u <= Y_MAX);
  }

  inf.readEof();
  return 0;
}
