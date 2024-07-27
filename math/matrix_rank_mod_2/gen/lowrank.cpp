#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;
using u64 = unsigned long long;

#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

struct My_Bitset {
  using T = My_Bitset;
  int N;
  vector<u64> dat;

  // x で埋める
  My_Bitset(int N = 0, int x = 0) : N(N) {
    assert(x == 0 || x == 1);
    u64 v = (x == 0 ? 0 : -1);
    dat.assign((N + 63) >> 6, v);
    if (N) dat.back() >>= (64 * int(dat.size()) - N);
  }

  class Proxy {
  public:
    Proxy(vector<u64> &d, int i) : dat(d), index(i) {}
    operator bool() const { return (dat[index >> 6] >> (index & 63)) & 1; }

    Proxy &operator=(u64 value) {
      dat[index >> 6] &= ~(u64(1) << (index & 63));
      dat[index >> 6] |= (value & 1) << (index & 63);
      return *this;
    }

  private:
    vector<u64> &dat;
    int index;
  };

  Proxy operator[](int i) { return Proxy(dat, i); }
  T &operator^=(const T &p) {
    assert(N == p.N);
    FOR(i, dat.size()) dat[i] ^= p.dat[i];
    return *this;
  }
  T operator^(const T &p) const { return T(*this) ^= p; }
};

using BS = My_Bitset;

vector<BS> gen_matrix(int n, int m, int r, Random &gen) {
  assert(r <= m && r <= n);
  vector<BS> a(n, BS(m));
  // 最初の r 行は適当に埋める
  FOR(i, r) FOR(j, m) { a[i][j] = gen.uniform_bool(); }
  // それ以外は最初の r 行の線形結合
  FOR(i, r, n) {
    FOR(k, r) {
      if (gen.uniform_bool()) a[i] ^= a[k];
    }
  }
  return a;
}

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 4096);
  int m = NM_MAX / n;
  if (seed % 2) swap(n, m);
  int rank = gen.uniform(1, min(n, m));

  auto a = gen_matrix(n, m, rank, gen);

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    string S(m, '0');
    for (int j = 0; j < m; ++j) S[j] = '0' + a[i][j];
    printf("%s\n", S.c_str());
  }
  return 0;
}
