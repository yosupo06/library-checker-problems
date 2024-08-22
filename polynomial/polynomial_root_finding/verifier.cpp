#include <algorithm>

#include "params.h"
#include "random.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(0, N_MAX, "N");
  inf.readChar('\n');

  for (int n = 0; n <= N; ++n) {
    if (n) inf.readSpace();
    int f = inf.readInt(0, MOD, "f");
    if (n == N) ensure(f != 0);
  }
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
