#include <iostream>
#include "params.h"
#include "testlib.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;

int main() {
  registerValidation();
  int Q = inf.readInt(MIN_Q, MAX_Q);
  inf.readChar('\n');
  for (int q = 0; q < Q; q++) {
    inf.readLong(MIN_N, MAX_N, "N");
    inf.readChar('\n');
  }
  inf.readChar('\n');
  return 0;
}
