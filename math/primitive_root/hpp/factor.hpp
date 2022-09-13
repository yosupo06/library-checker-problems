ll gcd(ll a, ll b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

ll RND(ll n) {
  static auto gen = Random(0);
  return gen.uniform<ll>(0, n - 1);
}

ll rho(ll n, ll c) {
  m64::set_mod(n);
  assert(n > 1);
  const m64 cc(c);
  auto f = [&](m64 x) { return x * x + cc; };
  m64 x = 1, y = 2, z = 1, q = 1;
  ll g = 1;
  const ll m = 1LL << (__lg(n) / 5); // ?
  for (ll r = 1; g == 1; r <<= 1) {
    x = y;
    for (int i = 0; i < r; ++i) y = f(y);
    for (ll k = 0; k < r and g == 1; k += m) {
      z = y;
      for (int i = 0; i < min(m, r - k); ++i) y = f(y), q *= x - y;
      g = gcd(q.val(), n);
    }
  }
  if (g == n) do {
      z = f(z);
      g = gcd((x - z).val(), n);
    } while (g == 1);
  return g;
}

ll find_prime_factor(ll n) {
  assert(n > 1);
  if (primetest(n)) return n;
  for (int i = 0; i < 100; ++i) {
    ll m = rho(n, RND(n));
    if (primetest(m)) return m;
    n = m;
  }
  cerr << "failed" << endl;
  assert(false);
  return -1;
}

vector<pi> factor(ll n) {
  assert(n >= 1);
  vector<pi> pf;
  for (int p = 2; p < 100; ++p) {
    if (p * p > n) break;
    if (n % p == 0) {
      ll e = 0;
      do { n /= p, e += 1; } while (n % p == 0);
      pf.emplace_back(p, e);
    }
  }
  while (n > 1) {
    ll p = find_prime_factor(n);
    ll e = 0;
    do { n /= p, e += 1; } while (n % p == 0);
    pf.emplace_back(p, e);
  }
  sort(pf.begin(), pf.end());
  return pf;
}

vector<pi> factor_by_lpf(ll n, vector<int>& lpf) {
  vector<pi> res;
  while (n > 1) {
    int p = lpf[n];
    int e = 0;
    while (n % p == 0) {
      n /= p;
      ++e;
    }
    res.emplace_back(p, e);
  }
  return res;
}
