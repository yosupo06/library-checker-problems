#include <algorithm>

#include "params.h"
#include "testlib.h"

using namespace std;
bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}
int main() {
  registerValidation();

  int t = inf.readInt(1, (int)T_MAX);
  inf.readSpace();
  int m = inf.readInt(1, (int)M_MAX);
  inf.readChar('\n');
  ensure(is_prime(m));
  for (int i = 0; i < t; i++) {
    inf.readLong(0LL, N_MAX);
    inf.readSpace();
    inf.readLong(0LL, N_MAX);
    inf.readChar('\n');
  }

  inf.readEof();
}
