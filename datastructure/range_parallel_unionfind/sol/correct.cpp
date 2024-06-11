#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;

#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }

template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a: A) sm += a;
  return sm;
}

struct UnionFind {
  int n, n_comp;
  vc<int> dat; // par or (-size)
  UnionFind(int n = 0) { build(n); }

  void build(int m) {
    n = m, n_comp = m;
    dat.assign(n, -1);
  }

  void reset() { build(n); }

  int operator[](int x) {
    while (dat[x] >= 0) {
      int pp = dat[dat[x]];
      if (pp < 0) { return dat[x]; }
      x = dat[x] = pp;
    }
    return x;
  }

  ll size(int x) {
    x = (*this)[x];
    return -dat[x];
  }

  bool merge(int x, int y) {
    x = (*this)[x], y = (*this)[y];
    if (x == y) return false;
    if (-dat[x] < -dat[y]) swap(x, y);
    dat[x] += dat[y], dat[y] = x, n_comp--;
    return true;
  }
};

struct Range_Parallel_UnionFind {
  int N;
  int log;
  // ufs[i][a]==ufs[i][b] iff [a,...,a+2^i) == [b,...,b+2^i)
  vc<UnionFind> ufs;
  Range_Parallel_UnionFind(int n) : N(n) {
    log = 1;
    while ((1 << log) < n) ++log;
    ufs.resize(log);
    FOR(i, log) {
      ll n = 1 << i;
      ufs[i].build(N - n + 1);
    }
  }

  // f(r1,r2) : 成分 r2 を r1 にマージ
  template <typename F>
  void merge(int L1, int R1, int L2, int R2, F f) {
    assert(R1 - L1 == R2 - L2);
    int n = R1 - L1;
    if (n == 0) return;
    if (n == 1) return merge_inner(0, L1, L2, f);
    int k = topbit(n - 1);
    merge_inner(k, L1, L2, f);
    merge_inner(k, R1 - (1 << k), R2 - (1 << k), f);
  }

  // f(r1,r2) : 成分 r2 を r1 にマージ
  template <typename F>
  void merge(int i, int j, F f) {
    merge_inner(0, i, j, f);
  }

  template <typename F>
  void merge_inner(int k, int L1, int L2, const F &f) {
    if (k == 0) {
      int a = ufs[0][L1], b = ufs[0][L2];
      if (a == b) return;
      ufs[0].merge(a, b);
      int c = ufs[0][a];
      return f(c, a ^ b ^ c);
    }
    if (!ufs[k].merge(L1, L2)) return;
    merge_inner(k - 1, L1, L2, f);
    merge_inner(k - 1, L1 + (1 << (k - 1)), L2 + (1 << (k - 1)), f);
  }
};

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;
  constexpr modint() : val(0) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
};

using mint = modint<998244353>;

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  Range_Parallel_UnionFind uf(N);
  vc<mint> x(N);
  FOR(i, N) {
    int a;
    scanf("%d", &a);
    x[i] = a;
  }

  mint ANS = SUM<mint>(x);
  auto f = [&](int i, int j) -> void {
    ANS += x[i] * x[j];
    x[i] += x[j];
  };

  FOR(Q) {
    int k, a, b;
    scanf("%d %d %d", &k, &a, &b);
    uf.merge(a, a + k, b, b + k, f);
    printf("%d\n", ANS.val);
  }
}

signed main() { solve(); }
