#pragma once

#include <string>
using namespace std;
#include "params.h"
#include "random.h"

using i128 = __int128_t;
using u128 = __uint128_t;
i128 TEN(int n) { return n ? TEN(n - 1) * 10 : 1; }
const i128 A_AND_B_MAX = TEN(LOG_10_A_AND_B_MAX);

// [0, x]
u128 uniform128_inner(Random& gen, u128 x) {
  if (x == 0) return 0;
  int lg = 0;
  if (x >> 64) {
    lg = 127 - __builtin_clzll(x >> 64);
  } else {
    lg = 63 - __builtin_clzll(x);
  }
  u128 mask = (lg == 127) ? ~u128(0) : (u128(1) << (lg + 1)) - 1;
  while (true) {
    u128 y = gen.uniform(0ULL, ~0ULL);
    y <<= 64;
    y |= gen.uniform(0ULL, ~0ULL);
    y &= mask;
    if (y <= x) return y;
  }
}

// [l, r]
i128 uniform128(Random& gen, i128 l, i128 r) {
  assert(l <= r);
  return l + uniform128_inner(gen, r - l);
}

i128 str_to_i128(string S) {
  if (S == "0") return 0;
  i128 res = 0;
  for (int i = S[0] == '-' ? 1 : 0; i < (int)S.size(); i++) {
    res = res * 10 + S[i] - '0';
  }
  if (S[0] == '-') res = -res;
  return res;
}

string i128_to_str(i128 x) {
  if (x == 0) return "0";
  bool neg = false;
  if (x < 0) neg = true, x = -x;
  string res;
  while (x) res.push_back(x % 10 + '0'), x /= 10;
  if (neg) res.push_back('-');
  reverse(begin(res), end(res));
  return res;
}
