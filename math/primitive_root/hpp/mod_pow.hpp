ll mod_pow_long(ll a, ll n, ll mod) {
  using i128 = __int128;
  a %= mod;
  ll p = a;
  ll v = 1;
  while (n) {
    if (n & 1) v = i128(v) * p % mod;
    p = i128(p) * p % mod;
    n >>= 1;
  }
  return v;
}
