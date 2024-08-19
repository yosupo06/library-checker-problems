#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template <typename mint>
std::pair<int, mint> GaussElimination(vector<vector<mint>> &a,
                                      int pivot_end = -1,
                                      bool diagonalize = false) {
  int H = a.size(), W = a[0].size();
  int rank = 0, je = pivot_end;
  if (je == -1) je = W;
  mint det = 1;
  for (int j = 0; j < je; j++) {
    int idx = -1;
    for (int i = rank; i < H; i++) {
      if (a[i][j] != mint(0)) {
        idx = i;
        break;
      }
    }
    if (idx == -1) {
      det = 0;
      continue;
    }
    if (rank != idx) {
      det = -det;
      swap(a[rank], a[idx]);
    }
    det *= a[rank][j];
    if (diagonalize && a[rank][j] != mint(1)) {
      mint coeff = a[rank][j].inverse();
      for (int k = j; k < W; k++) a[rank][k] *= coeff;
    }
    int is = diagonalize ? 0 : rank + 1;
    for (int i = is; i < H; i++) {
      if (i == rank) continue;
      if (a[i][j] != mint(0)) {
        mint coeff = a[i][j] / a[rank][j];
        for (int k = j; k < W; k++) a[i][k] -= a[rank][k] * coeff;
      }
    }
    rank++;
  }
  return make_pair(rank, det);
}

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const { return pow(mod - 2); }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};

template <typename mint>
vector<vector<mint>> inverse_matrix(const vector<vector<mint>> &a) {
  int N = a.size();
  assert(N > 0);
  assert(N == (int)a[0].size());

  vector<vector<mint>> m(N, vector<mint>(2 * N));
  for (int i = 0; i < N; i++) {
    copy(begin(a[i]), end(a[i]), begin(m[i]));
    m[i][N + i] = 1;
  }

  auto [rank, det] = GaussElimination(m, N, true);
  if (rank != N) return {};

  vector<vector<mint>> b(N);
  for (int i = 0; i < N; i++) {
    copy(begin(m[i]) + N, end(m[i]), back_inserter(b[i]));
  }
  return b;
}

using mint = LazyMontgomeryModInt<998244353>;

int main() {
  int n, x;
  scanf("%d", &n);
  vector<vector<mint>> a(n, vector<mint>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &x);
      a[i][j] = x;
    }
  }

  auto b = inverse_matrix(a);

  if (b.empty()) {
    printf("-1\n");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) printf(" ");
      printf("%d", b[i][j].get());
    }
    printf("\n");
  }
  return 0;
}
