#include <cstdio>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;
typedef long long i64;

Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
  Matrix H(M);
  int n = static_cast<int>(H.size());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((H[i][j] %= mod) < 0)
        H[i][j] += mod;
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    int pivot = i + 1;
    for (; pivot < n; ++pivot) {
      if (H[pivot][i] != 0)
        break;
    }
    if (pivot == n)
      continue;
    if (pivot != i + 1) {
      for (int j = i; j < n; ++j)
        std::swap(H[i + 1][j], H[pivot][j]);
      for (int j = 0; j < n; ++j)
        std::swap(H[j][i + 1], H[j][pivot]);
    }
    for (int j = i + 2; j < n; ++j) {
      for (;;) {
        if (H[j][i] == 0)
          break;
        if (H[i + 1][i] == 0) {
          for (int k = i; k < n; ++k)
            std::swap(H[i + 1][k], H[j][k]);
          for (int k = 0; k < n; ++k)
            std::swap(H[k][i + 1], H[k][j]);
          break;
        }
        if (H[j][i] >= H[i + 1][i]) {
          int q = H[j][i] / H[i + 1][i], mq = mod - q;
          for (int k = i; k < n; ++k)
            H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
          for (int k = 0; k < n; ++k)
            H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
        } else {
          int q = H[i + 1][i] / H[j][i], mq = mod - q;
          for (int k = i; k < n; ++k)
            H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
          for (int k = 0; k < n; ++k)
            H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
        }
      }
    }
  }
  return H;
}

std::vector<int> get_charpoly(const Matrix &M, int mod) {
  Matrix H(to_upper_Hessenberg(M, mod));
  int n = H.size();
  std::vector<std::vector<int>> p(n + 1);
  p[0] = {1 % mod};
  for (int i = 1; i <= n; ++i) {
    const std::vector<int> &pi_1 = p[i - 1];
    std::vector<int> &pi = p[i];
    pi.resize(i + 1, 0);
    int v = mod - H[i - 1][i - 1];
    if (v == mod)
      v = 0;
    for (int j = 0; j < i; ++j) {
      pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
      if ((pi[j + 1] += pi_1[j]) >= mod)
        pi[j + 1] -= mod;
    }
    int t = 1;
    for (int j = 1; j < i; ++j) {
      t = i64(t) * H[i - j][i - j - 1] % mod;
      int prod = i64(t) * H[i - j - 1][i - 1] % mod;
      if (prod == 0)
        continue;
      prod = mod - prod;
      for (int k = 0; k <= i - j - 1; ++k)
        pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
    }
  }
  return p[n];
}

int main() {
  int n, mod;
  std::scanf("%d%d", &n, &mod);
  Matrix M(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int v;
      std::scanf("%d", &v);
      M[i][j] = v;
    }
  }
  std::vector<int> charpoly(get_charpoly(M, mod));
  int res = charpoly[0];
  if (((n & 1) == 1) && (res = mod - res) == mod)
    res = 0;
  std::printf("%d\n", res);
  return 0;
}