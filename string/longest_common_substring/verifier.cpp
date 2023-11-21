#include <iostream>

#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
  registerValidation();

  string s = inf.readToken();
  inf.readChar('\n');
  string t = inf.readToken();
  inf.readChar('\n');
  inf.readEof();

  int n = int(s.size());
  int m = int(t.size());
  ensure(1 <= n && n <= N_MAX);
  ensure(1 <= m && m <= N_MAX);

  for (char c: s) { ensure(islower(c)); }
  for (char c: t) { ensure(islower(c)); }
  return 0;
}
