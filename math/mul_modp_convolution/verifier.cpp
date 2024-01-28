#include <iostream>

#include "params.h"
#include "testlib.h"

bool isPrime(int x) {
  if (x < 2) return false;
  for(int i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

int main() {
  registerValidation();

  int P = inf.readInt(P_MIN, P_MAX);
  inf.readChar('\n');
  inf.ensuref(isPrime(P), "P should be a prime");

  inf.readInts(P, 0, MOD - 1);
  inf.readChar('\n');

  inf.readInts(P, 0, MOD - 1);
  inf.readChar('\n');

  inf.readEof();
  return 0;
}
