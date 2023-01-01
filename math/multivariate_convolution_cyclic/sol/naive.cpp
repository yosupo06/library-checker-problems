#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

struct ArbitraryModInt {
  static constexpr bool is_modint = true;
  int val;
  ArbitraryModInt() : val(0) {}
  ArbitraryModInt(ll y)
      : val(y >= 0 ? y % get_mod()
                   : (get_mod() - (-y) % get_mod()) % get_mod()) {}
  bool operator<(const ArbitraryModInt &other) const {
    return val < other.val;
  } // To use std::map<ArbitraryModInt, T>
  static int &get_mod() {
    static int mod = 0;
    return mod;
  }
  static void set_mod(int md) { get_mod() = md; }
  ArbitraryModInt &operator+=(const ArbitraryModInt &p) {
    if ((val += p.val) >= get_mod()) val -= get_mod();
    return *this;
  }
  ArbitraryModInt &operator-=(const ArbitraryModInt &p) {
    if ((val += get_mod() - p.val) >= get_mod()) val -= get_mod();
    return *this;
  }
  ArbitraryModInt &operator*=(const ArbitraryModInt &p) {
    long long a = (long long)val * p.val;
    int xh = (int)(a >> 32), xl = (int)a, d, m;
    asm("divl %4; \n\t" : "=a"(d), "=d"(m) : "d"(xh), "a"(xl), "r"(get_mod()));
    val = m;
    return *this;
  }
  ArbitraryModInt &operator/=(const ArbitraryModInt &p) {
    *this *= p.inverse();
    return *this;
  }
  ArbitraryModInt operator-() const { return ArbitraryModInt(get_mod() - val); }
  ArbitraryModInt operator+(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) += p;
  }
  ArbitraryModInt operator-(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) -= p;
  }
  ArbitraryModInt operator*(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) *= p;
  }
  ArbitraryModInt operator/(const ArbitraryModInt &p) const {
    return ArbitraryModInt(*this) /= p;
  }
  bool operator==(const ArbitraryModInt &p) const { return val == p.val; }
  bool operator!=(const ArbitraryModInt &p) const { return val != p.val; }
  ArbitraryModInt inverse() const {
    int a = val, b = get_mod(), u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return ArbitraryModInt(u);
  }
  ArbitraryModInt pow(ll n) const {
    ArbitraryModInt ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
};

using mint = ArbitraryModInt;

int main() {
  int p;
  int k;
  scanf("%d", &p);
  scanf("%d", &k);
  mint::set_mod(p);
  vector<int> ns(k);
  int N = 1;
  for (int i = 0; i < k; i++) {
    scanf("%d", &(ns[i]));
    N *= ns[i];
  }
  vector<mint> f(N), g(N);
  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    f[i] = x;
  }
  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    g[i] = x;
  }
  vector<mint> fg(N);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int ij = 0;
      int x = i, y = j;
      int base = 1;
      for (int l = 0; l < k; l++) {
        int xl = x % ns[l];
        int yl = y % ns[l];
        int zl = (xl + yl) % ns[l];

        ij += base * zl;

        x /= ns[l];
        y /= ns[l];
        base *= ns[l];
      }
      fg[ij] += f[i] * g[j];
    }
  }

  for (int i = 0; i < N; i++) {
    printf("%d", fg[i].val);
    if (i + 1 < N) printf(" ");
  }
  printf("\n");
  return 0;
}
