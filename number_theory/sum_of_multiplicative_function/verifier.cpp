#include <algorithm>
#include <cassert>

#include "params.h"
#include "testlib.h"
using namespace std;

int main() {
  registerValidation();

  long long T = inf.readLong(1, T_MAX);
  inf.readChar('\n');

  // T sqrt(N) <= T_SqrtN_MAX
  long long n_max = -1;
  if (T == 1) {
    n_max = N_MAX;
  } else {
    n_max = T_sqrtN_MAX * T_sqrtN_MAX / (T * T);
  }

  for (int i = 0; i < T; i++) {
    inf.readLong(1, n_max);
    inf.readChar(' ');
    inf.readLong(0, MOD - 1);
    inf.readChar(' ');
    inf.readLong(0, MOD - 1);
    inf.readChar('\n');
  }

  inf.readEof();
}
