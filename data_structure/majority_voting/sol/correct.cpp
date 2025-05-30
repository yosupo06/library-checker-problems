#include <algorithm>
#include <cstdio>
#include <vector>

template <class Op> struct Segtree {
  using T = typename Op::S;
  int sz, lg;
  std::vector<T> v;

  template <class F> Segtree(int n, F f) : lg(1) {
    while ((1 << lg) < n) {
      ++lg;
    }
    sz = 1 << lg;
    v = std::vector<T>(2 * sz, Op::e());
    for (int i = 0; i < n; ++i) {
      v[sz + i] = f(i);
    }
    for (int i = sz - 1; i >= 0; --i) {
      update(i);
    }
  }

  void update(int k) { v[k] = Op::op(v[2 * k], v[2 * k + 1]); }

  void set(int p, T x) {
    p += sz;
    v[p] = x;
    for (int i = 1; i <= lg; ++i) {
      update(p >> i);
    }
  }

  T fold(int l, int r) {
    T sl = Op::e(), sr = Op::e();
    l += sz;
    r += sz;
    while (l < r) {
      if (l & 1) {
        sl = Op::op(sl, v[l++]);
      }
      if (r & 1) {
        sr = Op::op(v[--r], sr);
      }
      l >>= 1;
      r >>= 1;
    }
    return Op::op(sl, sr);
  }
};

struct MajorityVoting {
  using S = std::pair<int, int>;

  static S e() { return {0, 0}; }

  static S op(S l, S r) {
    auto [x, c] = l;
    auto [y, d] = r;
    if (x == y) {
      return {x, c + d};
    } else if (c >= d) {
      return {x, c - d};
    } else {
      return {y, d - c};
    }
  }
};

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

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

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

  Segtree<MajorityVoting> seg(N,
                              [&](int i) { return std::make_pair(A[i], 1); });

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
      seg.set(a, {b, 1});

      int i = std::lower_bound(xs[A[a]].begin(), xs[A[a]].end(), a) -
              xs[A[a]].begin();
      ft[A[a]].set(i, false);

      A[a] = b;

      i = std::lower_bound(xs[A[a]].begin(), xs[A[a]].end(), a) -
          xs[A[a]].begin();
      ft[A[a]].set(i, true);
    } else {
      int x = seg.fold(a, b).first;
      int l = std::lower_bound(xs[x].begin(), xs[x].end(), a) - xs[x].begin();
      int r = std::lower_bound(xs[x].begin(), xs[x].end(), b) - xs[x].begin();
      int c = ft[x].sum(l, r);
      if (c * 2 > b - a) {
        printf("%d\n", z[x]);
      } else {
        printf("-1\n");
      }
    }
  }

  return 0;
}
