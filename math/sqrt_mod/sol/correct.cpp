#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using Int = long long;

// xorshift
unsigned xrand() {
  static unsigned x = 314159265, y = 358979323, z = 846264338, w = 327950288;
  unsigned t = x ^ x << 11; x = y; y = z; z = w; return w = w ^ w >> 19 ^ t ^ t >> 8;
}

// a^-1 (mod m)
//   m > 0
Int modInv(Int a, Int m) {
  Int b = m, x = 1, y = 0, t;
  for (; ; ) {
    t = a / b; a -= t * b;
    if (a == 0) {
      assert(b == 1 || b == -1);
      if (b == -1) y = -y;
      return (y < 0) ? (y + m) : y;
    }
    x -= t * y;
    t = b / a; b -= t * a;
    if (b == 0) {
      assert(a == 1 || a == -1);
      if (a == -1) x = -x;
      return (x < 0) ? (x + m) : x;
    }
    y -= t * x;
  }
}

// Jacobi symbol (a/m)
//   m > 0, m: odd
int jacobi(Int a, Int m) {
  int s = 1;
  if (a < 0) a = a % m + m;
  for (; m > 1; ) {
    a %= m;
    if (a == 0) return 0;
    const int r = __builtin_ctz(a);
    if ((r & 1) && ((m + 2) & 4)) s = -s;
    a >>= r;
    if (a & m & 2) s = -s;
    std::swap(a, m);
  }
  return s;
}

// sqrt(a) (mod p)
//   p: prime, p < 2^31, -p^2 <= a <= P^2
//   (b + sqrt(b^2 - a))^((p+1)/2) in F_p(sqrt(b^2 - a))
vector<Int> modSqrt(Int a, Int p) {
  if (p == 2) return {a & 1};
  const int j = jacobi(a, p);
  if (j == 0) return {0};
  if (j == -1) return {};
  Int b, d;
  for (; ; ) {
    b = xrand() % p;
    d = (b * b - a) % p;
    if (d < 0) d += p;
    if (jacobi(d, p) == -1) break;
  }
  Int f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
  for (Int e = (p + 1) >> 1; e; e >>= 1) {
    if (e & 1) {
      tmp = (g0 * f0 + d * ((g1 * f1) % p)) % p;
      g1 = (g0 * f1 + g1 * f0) % p;
      g0 = tmp;
    }
    tmp = (f0 * f0 + d * ((f1 * f1) % p)) % p;
    f1 = (2 * f0 * f1) % p;
    f0 = tmp;
  }
  return (g0 < p - g0) ? vector<Int>{g0, p - g0} : vector<Int>{p - g0, g0};
}

// modSqrt
void unittest() {
  for (const Int p : {2, 3, 5, 7, 11, 13, 17, 19}) {
    int numRoots = 0;
    for (Int a = 0; a < p; ++a) {
      for (const Int x : modSqrt(a, p)) {
        assert(0 <= x && x < p);
        assert((x * x) % p == a);
        ++numRoots;
      }
    }
    assert(numRoots == p);
  }
}

// https://judge.yosupo.jp/problem/sqrt_mod
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // unittest();

  int numCases;
  cin >> numCases;
  for (int caseId = 0; caseId < numCases; ++caseId) {
    Int Y, P;
    cin >> Y >> P;
    const vector<Int> res = modSqrt(Y, P);
    cout << (res.empty() ? -1 : res[0]) << "\n";
  }
  return 0;
}
