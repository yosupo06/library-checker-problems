#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

using ll = long long;
using u64 = unsigned long long;
template <class T>
using vc = vector<T>;

// https://trap.jp/post/1224/
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

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}

struct My_Bitset {
  using T = My_Bitset;
  int N;
  vc<u64> dat;
  My_Bitset(int N = 0, int x = 0) : N(N) {
    assert(x == 0 || x == 1);
    u64 v = (x == 0 ? 0 : -1);
    dat.assign((N + 63) >> 6, v);
    if (N) dat.back() >>= (64 * len(dat) - N);
  }

  int size() { return N; }
  class Proxy {
  public:
    Proxy(vc<u64> &d, int i) : dat(d), index(i) {}
    operator bool() const { return (dat[index >> 6] >> (index & 63)) & 1; }

    Proxy &operator=(u64 value) {
      dat[index >> 6] &= ~(u64(1) << (index & 63));
      dat[index >> 6] |= (value & 1) << (index & 63);
      return *this;
    }
    void flip() {
      dat[index >> 6] ^= (u64(1) << (index & 63)); // XOR to flip the bit
    }

  private:
    vc<u64> &dat;
    int index;
  };

  Proxy operator[](int i) { return Proxy(dat, i); }
  T &operator^=(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) dat[i] ^= p.dat[i];
    return *this;
  }
  T operator^(const T &p) const { return T(*this) ^= p; }
};

using BS = My_Bitset;

const int MAX = (1 << 24) + 10;
char BUF[MAX];

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);
  if (N == 0 || M == 0) {
    printf("0\n");
    return;
  }
  bool bl = 0;
  if (N > M) {
    swap(N, M);
    bl = 1;
  }
  vc<BS> a(N, BS(M));

  if (!bl) {
    FOR(i, N) {
      scanf("%s", BUF);
      FOR(j, M) a[i][j] = BUF[j] - '0';
    }
  } else {
    FOR(i, M) {
      scanf("%s", BUF);
      FOR(j, N) a[j][i] = BUF[j] - '0';
    }
  }

  int rk = 0;
  FOR(j, M) {
    if (rk == N) break;
    if (!a[rk][j]) {
      FOR(i, rk + 1, N) if (a[i][j]) {
        swap(a[rk], a[i]);
        break;
      }
    }
    if (!a[rk][j]) continue;
    FOR(i, rk + 1, N) {
      if (a[i][j]) { a[i] ^= a[rk]; }
    }
    ++rk;
  }

  printf("%d\n", rk);
}

signed main() { solve(); }
