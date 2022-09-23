#include "testlib.h"
#include "random.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
#include "hpp/primetest.hpp"
#include "hpp/factor.hpp"
#include "hpp/mod_pow.hpp"

bool check_primitive_root(ll p, ll r) {
  for (auto&& [q, k]: factor(p - 1)) {
    if (mod_pow_long(r, (p - 1) / q, p) == 1) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int Q = inf.readInt();
  for (int q = 0; q < Q; ++q) {
    ll p = inf.readLong();
    ll r = ouf.readLong(0, p - 1);
    if (!check_primitive_root(p, r)) {
      quitf(_wa, "'%lld' is not a primitive root modulo '%lld'", r, p);
    }
  }

  if (ouf.seekEof()) {
    quitf(_ok, "OK");
  } else {
    quitf(_wa, "Participant output contains extra tokens");
  }
}
