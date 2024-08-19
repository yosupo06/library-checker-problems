#include <cstdio>
#include <vector>
#include "../acl.h"

using namespace std;
using namespace atcoder;

using mint998 = modint998244353;

vector<int> factorize(int x) {
  vector<int> primeFactors;
  for(int i = 2; i <= x; i++) {
    if (x % i == 0) {
      primeFactors.emplace_back(i);
      while(x % i == 0)
        x /= i;
    }
  }
  return primeFactors;
}

int primitiveRoot(int m) {
  vector<int> primeFactors = factorize(m - 1);
  for(int r = 1; ; r++) {
    bool isRoot = true;
    for(int pf : primeFactors) {
      if (modint tmp(r); tmp.pow((m - 1) / pf) == 1) {
        isRoot = false;
        break;
      }
    }
    if (isRoot)
      return r;
  }
}

int main() {
  int P;
  scanf("%d", &P);

  vector<mint998> a(P), b(P);
  for(int i = 0; i < P; i++) {
    int ai;
    scanf("%d", &ai);
    a[i] = ai;
  }
  for(int i = 0; i < P; i++) {
    int bi;
    scanf("%d", &bi);
    b[i] = bi;
  }

  modint::set_mod(P);
  int r = primitiveRoot(P);
  vector<int> powR(P - 1), logR(P);
  {
    modint tmp(1);
    for(int i = 0; i < P - 1; i++, tmp *= r)
      powR[i] = tmp.val(), logR[tmp.val()] = i;
  }

  vector<mint998> c(P - 1), d(P - 1);
  for(int i = 0; i < P; i++)
    c[logR[i]] = a[i], d[logR[i]] = b[i];

  c = convolution(c, d);
  for(int i = P - 1; i < 2 * P - 3; i++)
    c[i - (P - 1)] += c[i];
  c.resize(P - 1);

  a[0] = accumulate(a.begin(), a.end(), mint998(0)) * b[0] +
         accumulate(b.begin() + 1, b.end(), mint998(0)) * a[0];
  for(int i = 0; i < P - 1; i++)
    a[powR[i]] = c[i];

  for(int i = 0; i < P; i++)
    printf("%d%c", a[i].val(), " \n"[i + 1 == P]);

  return 0;
}
