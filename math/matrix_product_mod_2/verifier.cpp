#include <iostream>
#include <cstring>

#include "./params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int n = inf.readInt(1, N_MAX);
  inf.readSpace();
  int m = inf.readInt(1, N_MAX);
  inf.readSpace();
  int k = inf.readInt(1, N_MAX);
  inf.readChar('\n');

  for (int i = 0; i < n; i++) {
    string S = inf.readToken();
    inf.readChar('\n');
    ensure(int(S.size()) == m);
    for (char x: S) ensure(x == '0' || x == '1');
  }

  for (int i = 0; i < m; i++) {
    string S = inf.readToken();
    inf.readChar('\n');
    ensure(int(S.size()) == k);
    for (char x: S) ensure(x == '0' || x == '1');
  }

  inf.readEof();
  return 0;
}
