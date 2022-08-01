#include <algorithm>

#include "params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int t = inf.readInt(1, (int)T_MAX);
  inf.readSpace();
  inf.readInt(1, (int)M_MAX);
  inf.readChar('\n');

  for (int i = 0; i < t; i++) {
    long long n = inf.readLong(0LL, N_MAX);
    inf.readSpace();
    long long k = inf.readLong(0LL, N_MAX);
    ensure(k <= n);
    inf.readChar('\n');
  }

  inf.readEof();
}
