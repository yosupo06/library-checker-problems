#include "params.h"
#include "testlib.h"
#include <vector>

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(0, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(1, Q_MAX);
  inf.readChar('\n');

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    if (i) inf.readSpace();
    A[i] = inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');

  for (int i = 0; i < N - 1; ++i) { ensure(A[i] < A[i + 1]); }

  for (int i = 0; i < Q; i++) {
    int t = inf.readInt(0, 5);
    inf.readSpace();
    int x = inf.readInt(A_MIN, A_MAX);
    inf.readChar('\n');

    if (t == 2) ensure(1 <= x);
  }
  inf.readEof();
  return 0;
}
