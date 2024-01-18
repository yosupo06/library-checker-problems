#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();

  int n = inf.readInt(1, N_MAX);
  inf.readChar(' ');
  int q = inf.readInt(1, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i < n; i++) {
    int l = inf.readInt(0, COORD_MAX);
    inf.readSpace();
    int d = inf.readInt(0, COORD_MAX);
    inf.readSpace();
    int r = inf.readInt(0, COORD_MAX);
    inf.readSpace();
    int u = inf.readInt(0, COORD_MAX);
    inf.readSpace();
    inf.readInt(0, WEIGHT_MAX, "w");
    inf.readChar('\n');

    ensure(l < r);
    ensure(d < u);
  }

  for (int i = 0; i < q; i++) {
    int t = inf.readInt(0, 1);
    inf.readSpace();
    if (t == 0) {
      int l = inf.readInt(0, COORD_MAX);
      inf.readSpace();
      int d = inf.readInt(0, COORD_MAX);
      inf.readSpace();
      int r = inf.readInt(0, COORD_MAX);
      inf.readSpace();
      int u = inf.readInt(0, COORD_MAX);
      inf.readSpace();
      inf.readInt(0, WEIGHT_MAX, "w");
      inf.readChar('\n');
      ensure(l < r);
      ensure(d < u);
    } else {
      inf.readInt(0, COORD_MAX, "x");
      inf.readSpace();
      inf.readInt(0, COORD_MAX, "y");
      inf.readChar('\n');
    }
  }
  inf.readEof();
  return 0;
}
