#include "testlib.h"
#include "params.h"
using namespace std;

int main() {
  registerValidation();

  string S = inf.readToken();
  inf.readChar('\n');
  inf.readEof();

  int n = S.size();
  ensure(MIN_N <= n && n <= MAX_N);

  for (char ch: S) ensure('a' <= ch && ch <= 'z');
  return 0;
}
