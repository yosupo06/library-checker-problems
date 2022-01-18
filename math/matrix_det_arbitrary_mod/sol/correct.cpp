#include <cstdio>
#include <vector>

int det(std::vector<std::vector<int>> m, int mod) {
  // if (mod == 1) return 0;
  int n = static_cast<int>(m.size());
  if (n == 0) return 1;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     if ((m[i][j] %= mod) < 0) m[i][j] += mod;
  //   }
  // }
  int res = 1, flip = 0;
  for (int i = 0; i < n; ++i) {
    int pivot_row = -1;
    for (int j = i; j < n; ++j) {
      if (m[j][i] != 0) {
        pivot_row = j;
        break;
      }
    }
    if (pivot_row == -1) return 0;
    if (pivot_row != i) {
      m[i].swap(m[pivot_row]);
      flip ^= 1;
    }
    for (int j = i + 1; j < n; ++j) {
      int mii = m[i][i], mji = m[j][i];
      if (mji == 0) continue;
      // `a0` * `m[i][i]` + `a1` * `m[j][i]`
      // `b0` * `m[i][i]` + `b1` * `m[j][i]`
      // Use Euclidean algorithm to compute `a0, a1, b0, b1`.
      long long a0 = 1, a1 = 0, b0 = 0, b1 = 1;
      while ((mii != 0) && (mji != 0)) {
        if (mii < mji) {
          int q = mji / mii;
          mji -= q * mii;
          // (`b0`, `b1`) <- (`b0 - a0 * q`, `b1 - a1 * q`)
          b0 -= a0 * q;
          b1 -= a1 * q;
          if ((b0 %= mod) < 0) b0 += mod;
          if ((b1 %= mod) < 0) b1 += mod;
        } else {
          int q = mii / mji;
          mii -= q * mji;
          // (`a0`, `a1`) <- (`a0 - b0 * q`, `a1 - b1 * q`)
          a0 -= b0 * q;
          a1 -= b1 * q;
          if ((a0 %= mod) < 0) a0 += mod;
          if ((a1 %= mod) < 0) a1 += mod;
        }
      }
      for (int k = i; k < n; ++k) {
        int mik = m[i][k], mjk = m[j][k];
        m[i][k] = (mik * a0 + mjk * a1) % mod;
        m[j][k] = (mik * b0 + mjk * b1) % mod;
      }
      if (mii == 0) {
        m[i].swap(m[j]);
        flip ^= 1;
      }
    }
    res = static_cast<long long>(res) * m[i][i] % mod;
    if (res == 0) return 0; // In case of det(`m`) | `mod` when `mod` is not a prime. e.g. (2 * 3) modulo 6 = 0.
  }
  return static_cast<bool>(flip) ? (mod - res) : res; // `res` will never be 0 here.
}

int main() {
  int n, mod;
  std::scanf("%d%d", &n, &mod);
  std::vector<std::vector<int>> m(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int v;
      std::scanf("%d", &v);
      m[i][j] = v;
    }
  }
  std::printf("%d\n", det(m, mod));
  return 0;
}