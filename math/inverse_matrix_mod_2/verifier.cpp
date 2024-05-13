#include <iostream>
#include <cstring>

#include "./params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  int n = inf.readInt(1, N_MAX);
  inf.readChar('\n');

  for (int i = 0; i < n; i++) {
    string S = inf.readToken();
    inf.readChar('\n');
    ensure(int(S.size()) == n);
    for (char x: S) ensure(x == '0' || x == '1');
  }
  inf.readEof();
  return 0;
}
