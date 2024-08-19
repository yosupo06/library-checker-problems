#include "testlib.h"

#include "params.h"

#include <set>

using namespace std;
using ll = long long;

int main() {
  registerValidation();

  int N = inf.readInt(0, MAX_N);
  inf.readChar(' ');
  int a = inf.readInt(0, MOD - 1);
  inf.readChar(' ');
  int r = inf.readInt(0, MOD - 1);
  inf.readChar('\n');

  for (int i = 0; i < N; i++) {
    if (i) inf.readChar(' ');
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');
  inf.readEof();

  // check ar^i
  set<int> s;
  ll x = a;
  for (int i = 0; i < N; ++i) {
    s.insert(x);
    x = x * r % MOD;
  }
  ensure(int(s.size()) == N);

  return 0;
}