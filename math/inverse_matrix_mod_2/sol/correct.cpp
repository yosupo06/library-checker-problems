#include <vector>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <numeric>

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

int popcnt(u64 x) { return __builtin_popcountll(x); }

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

  void resize(int size) {
    dat.resize((size + 63) >> 6);
    int remainingBits = size & 63;
    if (remainingBits != 0) {
      u64 mask = (u64(1) << remainingBits) - 1;
      dat.back() &= mask;
    }
    N = size;
  }

  // thanks to chatgpt!
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

  bool operator==(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) if (dat[i] != p.dat[i]) return false;
    return true;
  }

  T &operator&=(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) dat[i] &= p.dat[i];
    return *this;
  }
  T &operator|=(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) dat[i] |= p.dat[i];
    return *this;
  }
  T &operator^=(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) dat[i] ^= p.dat[i];
    return *this;
  }
  T operator&(const T &p) const { return T(*this) &= p; }
  T operator|(const T &p) const { return T(*this) |= p; }
  T operator^(const T &p) const { return T(*this) ^= p; }
};

// det = 0 の場合には empty をかえす
template <typename BS>
vc<BS> mat_inv(vc<BS> A) {
  int N = len(A);
  vc<BS> B(N);
  if constexpr (is_same_v<BS, My_Bitset>) { FOR(i, N) B[i] = BS(N); }
  FOR(i, N) B[i][i] = 1;
  FOR(i, N) {
    FOR(k, i + 1, N) if (A[k][i]) {
      swap(A[k], A[i]);
      swap(B[k], B[i]);
      break;
    }
    if (!A[i][i]) return {};
    FOR(k, N) {
      if (i == k) continue;
      if (A[k][i]) {
        A[k] ^= A[i];
        B[k] ^= B[i];
      }
    }
  }
  return B;
}

template <typename BS>
bool det(vc<BS> A) {
  int N = len(A);
  FOR(i, N) {
    FOR(k, i + 1, N) if (A[k][i]) {
      swap(A[k], A[i]);
      break;
    }
    if (!A[i][i]) return 0;
    FOR(k, i + 1, N) {
      if (A[k][i]) { A[k] ^= A[i]; }
    }
  }
  return 1;
}

using BS = My_Bitset;

const int MAX = 4096 + 10;
char BUF[MAX];

void solve() {
  int N;
  scanf("%d", &N);

  vc<BS> A(N, BS(N));
  FOR(i, N) {
    scanf("%s", BUF);
    for (int j = 0; j < N; ++j) { A[i][j] = (BUF[j] - '0'); }
  }

  vc<BS> B = mat_inv<BS>(A);

  if (B.empty()) {
    assert(det<BS>(A) == 0);
    printf("-1\n");
  } else {
    // check matrix product
    vc<BS> C(N, BS(N));
    FOR(i, N) FOR(j, N) {
      if (A[i][j]) C[i] ^= B[j];
    }
    FOR(i, N) FOR(j, N) {
      bool a = (i == j);
      bool b = C[i][j];
      assert(a == b);
    }

    FOR(i, N) {
      FOR(j, N) { printf("%d", 1 * B[i][j]); }
      printf("\n");
    }
  }
}

signed main() {
  solve();
  return 0;
}
