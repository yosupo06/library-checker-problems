#include "params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(1, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(1, Q_MAX);
  inf.readChar('\n');

  while(Q--) {
    int t = inf.readInt(0, 1);
    inf.readSpace();
    inf.readInt(0, N - 1);
    inf.readSpace();
    inf.readInt(0, N - 1);
    if (t == 0) {
      inf.readSpace();
      inf.readInt(0, MOD - 1);
    }
    inf.readChar('\n');
  }

  inf.readEof();

  return 0;
}
