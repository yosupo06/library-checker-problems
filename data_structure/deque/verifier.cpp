#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();

  int q = inf.readInt(MIN_Q, MAX_Q, "Q");
  inf.readChar('\n');

  int length = 0;
  for (int i = 0; i < q; i++) {
    int t = inf.readInt(0, 4, "t");
    if (t == 0 || t == 1) {
      inf.readSpace();
      inf.readInt(MIN_X, MAX_X, "x");
      length++;
    } else if (t == 2 || t == 3) {
      length--;
      ensure(length >= 0);
    } else {
      inf.readSpace();
      inf.readInt(0, length - 1, "i");
    }
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
