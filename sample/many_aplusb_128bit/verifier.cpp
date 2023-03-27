#include <string>

#include "params.h"
#include "testlib.h"
using namespace std;

#include "base.hpp"

int main() {
  registerValidation();

  string MAX = i128_to_str(A_AND_B_MAX);

  // check if -MAX <= S <= MAX
  auto check = [&](string S) -> bool {
    if (S.empty()) return false;
    // 0
    if (S == "0") return true;
    if (S[0] == '-') S.erase(begin(S));
    if ((int)S.size() >= (int)MAX.size()) {
      return S <= MAX;
    }
    for (int i = 0; i < (int)S.size(); i++) {
      if (i == 0 and S[i] == '0') return false;
      if (!('0' <= S[i] and S[i] <= '9')) return false;
    }
    return true;
  };

  int t = inf.readInt(1, T_MAX);
  inf.readChar('\n');
  for (int i = 0; i < t; i++) {
    string A = inf.readToken();
    inf.readSpace();
    string B = inf.readToken();
    inf.readChar('\n');

    ensure(check(A));
    ensure(check(B));
  }
  inf.readEof();
  return 0;
}
