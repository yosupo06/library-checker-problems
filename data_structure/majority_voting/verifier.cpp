#include "params.h"
#include "testlib.h"
#include <vector>

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    if (i)
      inf.readSpace();
    A[i] = inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');

  for (int i = 0; i < Q; i++) {
    int t = inf.readInt(0, 1);
    inf.readSpace();

    if (t == 0) {
      inf.readInt(0, N - 1);
      inf.readSpace();
      inf.readInt(A_MIN, A_MAX);
    } else {
      int l = inf.readInt(0, N - 1);
      inf.readSpace();
      inf.readInt(l + 1, N);
    }
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
