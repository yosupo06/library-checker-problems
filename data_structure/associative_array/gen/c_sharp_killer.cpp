#include <cstdio>

using namespace std;

int main() {
  // long long MAXI = 1000000000000000000ll;
  int Q = 1000000;
  // long long mask = (1ll << 32) - 1;

  printf("%d\n", Q);

  int query0_col = 200000;
  int query0_one = 200000;
  int query1 = 600000;

  for (int i = 0; i < query0_col; i++) {
    long long v = 1;

    // https://yuinore.net/2017/04/tuple-is-god/
    // since long.GetHashCode() returns (x ^ y) where x, y := upper/lower 32
    // bits of the value, we can easily collide hash for long
    long long k1 = ((long long)i << 32) | i;
    printf("%d %lld %lld\n", 0, k1, v);
  }

  for (int i = 0; i < query0_one; i++) {
    long long v = 2;
    printf("%d %lld %lld\n", 0, 0ll, v);
  }

  for (int i = 0; i < query1; i++) {
    printf("%d %lld\n", 1, ((long long)i << 32) | i);
  }
  return 0;
}