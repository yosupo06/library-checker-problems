#include "random.h"
#include <algorithm>
#include <cstdio>
#include <tuple>
#include <unordered_map>
#include <vector>

struct FenwickTree {
  int n;
  std::vector<int> v;

  FenwickTree(int _n = 0) : n(_n), v(n) {}

  void add(int i, int x) {
    ++i;
    while (i <= n) {
      v[i - 1] += x;
      i += i & -i;
    }
  }

  int sum(int i) {
    int s = 0;
    while (i > 0) {
      s += v[i - 1];
      i -= i & -i;
    }
    return s;
  }

  int sum(int a, int b) { return sum(b) - sum(a); }
};

using u64 = unsigned long long;
std::size_t popcount64(u64 x) {
#ifdef __GNUC__
  return __builtin_popcountll(x);
#else
  x -= x >> 1 & 0x5555555555555555;
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
  return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}

struct FenwickTree01 {
  std::vector<u64> a;
  FenwickTree ft;

  FenwickTree01(int n = 0) {
    int m = (n + 63) / 64;
    a = std::vector<u64>(m);
    ft = FenwickTree(m);
  }

  void set(int i, bool f) {
    int j = i % 64;
    i /= 64;
    int x = (a[i] >> j) & 1;
    if (x && !f) {
      a[i] ^= 1ULL << j;
      ft.add(i, -1);
    } else if (!x && f) {
      a[i] |= 1ULL << j;
      ft.add(i, 1);
    }
  }

  int sum(int i) {
    int j = i % 64;
    i /= 64;
    int s = ft.sum(i);
    if (j) {
      s += popcount64(a[i] & ((1ULL << j) - 1));
    }
    return s;
  }

  int sum(int a, int b) { return sum(b) - sum(a); }
};

const int W = 50;

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  Random gen(0);

  std::vector<int> z = A;
  std::vector<std::tuple<int, int, int>> queries;

  for (int q = 0; q < Q; ++q) {
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    queries.emplace_back(t, a, b);
    if (t == 0) {
      z.push_back(b);
    }
  }

  std::sort(z.begin(), z.end());
  z.erase(std::unique(z.begin(), z.end()), z.end());
  int M = z.size();
  std::vector<std::vector<int>> xs(M);

  for (int i = 0; i < N; ++i) {
    A[i] = std::lower_bound(z.begin(), z.end(), A[i]) - z.begin();
    xs[A[i]].push_back(i);
  }
  for (int i = 0; i < Q; ++i) {
    auto [t, a, b] = queries[i];
    if (t == 0) {
      b = std::lower_bound(z.begin(), z.end(), b) - z.begin();
      queries[i] = {t, a, b};
      xs[b].push_back(a);
    }
  }

  for (int i = 0; i < M; ++i) {
    std::sort(xs[i].begin(), xs[i].end());
    xs[i].erase(std::unique(xs[i].begin(), xs[i].end()), xs[i].end());
  }

  std::vector<FenwickTree01> ft(M);
  for (int i = 0; i < M; ++i) {
    ft[i] = FenwickTree01(xs[i].size());
  }
  for (int i = 0; i < N; ++i) {
    int j = std::lower_bound(xs[A[i]].begin(), xs[A[i]].end(), i) -
            xs[A[i]].begin();
    ft[A[i]].set(j, true);
  }

  for (auto [t, a, b] : queries) {
    if (t == 0) {
      int i = std::lower_bound(xs[A[a]].begin(), xs[A[a]].end(), a) -
              xs[A[a]].begin();
      ft[A[a]].set(i, false);

      A[a] = b;

      i = std::lower_bound(xs[A[a]].begin(), xs[A[a]].end(), a) -
          xs[A[a]].begin();
      ft[A[a]].set(i, true);
    } else if (b - a <= W) {
      int m = -1, c = 0;
      for (int i = a; i < b; ++i) {
        if (c == 0 || m == A[i]) {
          m = A[i];
          ++c;
        } else {
          --c;
        }
      }

      c = 0;
      for (int i = a; i < b; ++i) {
        if (A[i] == m) {
          ++c;
        }
      }
      if (c * 2 > b - a) {
        printf("%d\n", z[m]);
      } else {
        printf("-1\n");
      }
    } else {
      std::unordered_map<int, int> cnt;
      for (int it = 0; it < W; ++it) {
        int i = gen.uniform(a, b - 1);
        ++cnt[A[i]];
      }

      std::vector<std::pair<int, int>> v;
      for (auto [k, c] : cnt) {
        v.emplace_back(c, k);
      }
      std::sort(v.begin(), v.end(), std::greater<std::pair<int, int>>());

      int res = -1;
      for (int i = 0; i < std::min<int>(v.size(), 2); ++i) {
        int m = v[i].second;
        int l = std::lower_bound(xs[m].begin(), xs[m].end(), a) - xs[m].begin();
        int r = std::lower_bound(xs[m].begin(), xs[m].end(), b) - xs[m].begin();
        int c = ft[m].sum(l, r);
        if (c * 2 > b - a) {
          res = m;
          break;
        }
      }

      printf("%d\n", res == -1 ? -1 : z[res]);
    }
  }

  return 0;
}
