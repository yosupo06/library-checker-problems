#include <vector>
#include <cassert>
#include <cstring>

using namespace std;
using ll = long long;
using u64 = unsigned long long;

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

template <class T>
using vc = vector<T>;

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())

struct My_Bitset {
  using T = My_Bitset;
  int N;
  vc<u64> dat;

  My_Bitset(int N = 0) : N(N) { dat.assign((N + 63) >> 6, 0); }
  int size() { return N; }

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
  T &operator^=(const T &p) {
    assert(N == p.N);
    FOR(i, len(dat)) dat[i] ^= p.dat[i];
    return *this;
  }
  T operator^(const T &p) const { return T(*this) ^= p; }
};

template <typename BS>
int det(vc<BS> A) {
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

void gen_and_out(Random &gen, int N, int ans) {
  // random matrix det mod 2
  // 0.29: det=1
  // 0.71: det=0
  // ランダムに作って判定すればよい
  using BS = My_Bitset;
  vc<BS> mat(N, BS(N));
  while (1) {
    FOR(i, N) FOR(j, N) { mat[i][j] = gen.uniform<int>(0, 1); }
    if (det(mat) != ans) continue;
    printf("%d\n", N);
    FOR(i, N) {
      string S(N, '0');
      FOR(j, N) if (mat[i][j]) S[j] = '1';
      printf("%s\n", S.c_str());
    }
    return;
  }
}