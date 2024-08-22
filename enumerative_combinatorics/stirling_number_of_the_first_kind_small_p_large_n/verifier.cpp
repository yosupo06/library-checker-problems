#include <algorithm>

#include "params.h"
#include "testlib.h"

using namespace std;

bool is_prime(int p) {
  if (p <= 1) return false;
  for (int i = 2; i < p; ++i)
    if (p % i == 0) return false;
  return true;
}

int main() {
  registerValidation();

  int T = inf.readInt(1, T_MAX);
  inf.readSpace();
  int p = inf.readInt(1, P_MAX);
  inf.readChar('\n');

  ensure(is_prime(p));

  for (int t = 0; t < T; t++) {
    long long n = inf.readLong(0LL, N_MAX);
    inf.readSpace();
    long long k = inf.readLong(0LL, N_MAX);
    ensure(k <= n);
    inf.readChar('\n');
  }

  inf.readEof();
}
