#include <algorithm>

#include "params.h"
#include "random.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();

  string MAX(LOG_10_A_AND_B_MAX + 1, '0');
  MAX[0] = '1';

  // check if (S is integer) and (-MAX <= S <= MAX)
  auto check = [&](string S) -> bool {
    if (!S.empty() && S[0] == '-') S = S.substr(1);
    if (S.empty()) return false;
    if (S == "0") return true;

    for (int i = 0; i < (int)S.size(); i++) {
      if (i == 0 and S[i] == '0') return false;
      if (!('0' <= S[i] and S[i] <= '9')) return false;
    }
    return (int)S.size() <= LOG_10_A_AND_B_MAX;
  };

  int t = inf.readLong(1, T_MAX);
  inf.readChar('\n');

  long long length_sum = 0;
  while (t--) {
    string a = inf.readToken();
    inf.readSpace();
    string b = inf.readToken();
    inf.readChar('\n');

    ensure(check(a));
    ensure(check(b));
    length_sum += a.size() + b.size();
  }

  ensure(length_sum <= SUM_OF_CHARACTER_LENGTH);
  inf.readEof();
}
