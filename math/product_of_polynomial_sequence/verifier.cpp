#include <iostream>

#include "params.h"
#include "testlib.h"

using namespace std;
using ll = long long;

int main() {
  registerValidation();
  int N = inf.readInt(0, N_MAX);
  inf.readChar('\n');

  ll d_sum = 0;
  for (int i = 0; i < N; ++i) {
    int D = inf.readInt(0, D_MAX);
    d_sum += D;
    inf.readSpace();
    for (int j = 0; j <= D; ++j) {
      if (j) inf.readSpace();
      int coef = inf.readInt(0, MOD - 1);
      if (j == D) ensure(coef != 0);
    }
    inf.readChar('\n');
  }

  ensure(0 <= d_sum && d_sum <= D_MAX);
  inf.readEof();
  return 0;
}
