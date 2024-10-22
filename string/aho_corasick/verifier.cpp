#include "testlib.h"
#include "params.h"
using namespace std;

int main() {
  registerValidation();

  int n = inf.readInt(MIN_N, MAX_N, "N");
  inf.readChar('\n');

  long long s_sum = 0;
  for (int i = 0; i < n; ++i) {
    string S = inf.readToken();
    inf.readChar('\n');

    ensure(MIN_S_SUM <= int(S.size()) && int(S.size()) <= MAX_S_SUM);
    for (char ch: S) ensure('a' <= ch && ch <= 'z');
    s_sum += S.size();
  }
  inf.readEof();

  ensure(MIN_S_SUM <= s_sum && s_sum <= MAX_S_SUM);
  return 0;
}
