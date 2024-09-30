#include <iostream>
#include <cstring>
#include "params.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();
  int n = inf.readInt(1, N_MAX);
  inf.readSpace();
  int m = inf.readInt(1, M_MAX);
  inf.readChar('\n');
  for (int i = 0; i < n; i++) {
    string S = inf.readToken();
    inf.readChar('\n');
    ensure(int(S.size()) == m);
    for (auto& ch: S) { ensure(ch == '0' || ch == '1'); }
  }
  string S = inf.readToken();
  inf.readChar('\n');
  ensure(int(S.size()) == n);
  for (auto& ch: S) { ensure(ch == '0' || ch == '1'); }
  inf.readEof();
  return 0;
}
