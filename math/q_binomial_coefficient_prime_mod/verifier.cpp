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
  inf.readSpace();
  inf.readInt(0, m - 1, "q");
  inf.readChar('\n');
  ensure(is_prime(m));
  const int upper = std::min<int>(m, N_MAX) - 1;
  for (int i = 0; i < t; i++) {
    inf.readInt(0, upper);
    inf.readSpace();
    inf.readInt(0, upper);
    inf.readChar('\n');
  }

  inf.readEof();
}
