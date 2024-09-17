#include <cstdlib>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cassert>
#include <tuple>
#include <string>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

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

int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a: A) sm += a;
  return sm;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

struct My_Bitset {
  using T = My_Bitset;
  int N;
  vc<u64> dat;

  // x で埋める
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

  static string TO_STR[256];
  string to_string() const {
    if (TO_STR[0].empty()) precompute();
    string S;
    for (auto &x: dat) { FOR(i, 8) S += TO_STR[(x >> (8 * i) & 255)]; }
    S.resize(N);
    return S;
  }

  static void precompute() {
    FOR(s, 256) {
      string x;
      FOR(i, 8) x += '0' + (s >> i & 1);
      TO_STR[s] = x;
    }
  }
};
string My_Bitset::TO_STR[256];

vc<My_Bitset> solve_linear(int n, int m, vc<My_Bitset> A, My_Bitset b) {
  using BS = My_Bitset;
  assert(len(b) == n);
  int rk = 0;
  FOR(j, m) {
    if (rk == n) break;
    FOR(i, rk + 1, n) if (A[i][j]) {
      swap(A[rk], A[i]);
      if (b[rk] != b[i]) b[rk] = !b[rk], b[i] = !b[i];
      break;
    }
    if (!A[rk][j]) continue;
    FOR(i, n) if (i != rk) {
      if (A[i][j]) { b[i] = b[i] ^ b[rk], A[i] = A[i] ^ A[rk]; }
    }
    ++rk;
  }
  FOR(i, rk, n) if (b[i]) return {};
  vc<BS> res(1, BS(m));

  vc<int> pivot(m, -1);
  int p = 0;
  FOR(i, rk) {
    while (!A[i][p]) ++p;
    res[0][p] = bool(b[i]), pivot[p] = i;
  }
  FOR(j, m) if (pivot[j] == -1) {
    BS x(m);
    x[j] = 1;
    FOR(k, j) if (pivot[k] != -1 && A[pivot[k]][j]) x[k] = 1;
    res.eb(x);
  }
  return res;
}

void solve() {
  int N, M;
  scanf("%d %d\n", &N, &M);
  using BS = My_Bitset;
  auto get = [&](int n) -> BS {
    BS x(n);
    char c;
    for (int i = 0; i < n; ++i) {
      scanf("%c", &c);
      x[i] = c - '0';
    }
    scanf("%c", &c);
    assert(c == '\n');
    return x;
  };
  vc<BS> A(N);
  FOR(i, N) A[i] = get(M);
  BS b = get(N);
  auto ANS = solve_linear(N, M, A, b);
  if (ANS.empty()) {
    printf("-1\n");
    return;
  }
  int R = len(ANS) - 1;
  printf("%d\n", R);
  for (auto &x: ANS) {
    string ans = x.to_string();
    printf("%s\n", ans.c_str());
  }
}

signed main() { solve(); }
