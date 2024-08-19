#include <iostream>

#include "params.h"
#include "testlib.h"

using namespace std;

bool is_convex(vector<int>& a) {
  int n = a.size();
  for (int i = 0; i < n - 2; ++i) {
    if (a[i + 1] - a[i] > a[i + 2] - a[i + 1]) return false;
  }
  return true;
}

int main() {
  registerValidation();
  int n = inf.readInt(1, N_MAX);
  inf.readSpace();
  int m = inf.readInt(1, N_MAX);
  inf.readChar('\n');
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) {
    if (i) inf.readSpace();
    a[i] = inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');
  for (int i = 0; i < m; i++) {
    if (i) inf.readSpace();
    b[i] = inf.readInt(A_MIN, A_MAX);
  }
  inf.readChar('\n');

  ensure(is_convex(a));

  inf.readEof();
  return 0;
}
