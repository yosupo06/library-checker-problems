#include <iostream>
#include "params.h"
#include "testlib.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
#include "hpp/primetest.hpp"

int main() {
  registerValidation();
  int Q = inf.readInt(MIN_Q, MAX_Q);
  inf.readChar('\n');
  for (int q = 0; q < Q; q++) {
    ll p = inf.readLong(MIN_P, MAX_P, "P");
    inf.readChar('\n');
    ensure(primetest(p));
  }
  inf.readEof();
  return 0;
}
