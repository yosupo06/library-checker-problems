#include "testlib.h"
#include "params.h"
#include <vector>

using namespace std;

int main() {
  registerValidation();

  int n = inf.readInt(N_MIN, N_MAX, "N");
  inf.readSpace();
  int q = inf.readInt(Q_MIN, Q_MAX, "Q");
  inf.readChar('\n');

  set<int> s;

  vector<bool> done(n);
  for (int i = 0; i < n; i++) {
    int p = inf.readInt(P_MIN, P_MAX, "p");
    inf.readSpace();
    inf.readInt(1, MOD - 1, "a");
    inf.readSpace();
    inf.readInt(0, MOD - 1, "b");
    inf.readChar('\n');

    ensure(!s.count(p));
    s.insert(p);
  }

  for (int i = 0; i < q; i++) {
    int t = inf.readInt(0, 3, "t");
    inf.readSpace();
    if (t == 0) {
      inf.readInt(0, n - 1, "i");
      inf.readSpace();
      int p = inf.readInt(P_MIN, P_MAX, "p");
      inf.readSpace();
      inf.readInt(1, MOD - 1, "a");
      inf.readSpace();
      inf.readInt(0, MOD - 1, "b");

      ensure(!s.count(p));
      s.insert(p);
    }
    if (t == 1) {
      int l = inf.readInt(0, n - 1, "l");
      inf.readSpace();
      inf.readInt(l + 1, n, "r");
      inf.readSpace();
      inf.readInt(0, MOD - 1, "x");
    }
    if (t == 2 || t == 3) {
      int l = inf.readInt(0, n - 1, "l");
      inf.readSpace();
      inf.readInt(l + 1, n, "r");
    }
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
