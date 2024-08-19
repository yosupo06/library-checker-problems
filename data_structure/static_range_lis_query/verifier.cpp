#include <vector>

#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  const int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  std::vector<bool> used(N, false);
  for (int i = 0; i < N; i++) {
    const int p = inf.readInt(0, N - 1);
    if (i + 1 < N) {
      inf.readSpace();
    } else {
      inf.readChar('\n');
    }

    ensure(!used[p]);
    used[p] = true;
  }

  for (int i = 0; i < Q; i++) {
    const int l = inf.readInt(0, N);
    inf.readSpace();
    inf.readInt(l, N);
    inf.readChar('\n');
  }

  inf.readEof();

  return 0;
}
