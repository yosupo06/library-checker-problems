#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <vector>

class range_inversions_query {
  using usize = std::size_t;
  using u64 = std::uint64_t;

  class bucket_type {
  public:
    std::vector<usize> rank;
    std::vector<usize> sorted_ind;
    std::vector<u64> prefix_inv;
    std::vector<u64> block_inv;
    std::vector<usize> freq;
  };

  usize bsize;
  std::vector<bucket_type> buckets;

public:
  range_inversions_query(const std::vector<usize> &rank) {
    const usize n = rank.size();
    bsize = std::sqrt(n) + 1;
    buckets = std::vector<bucket_type>(n / bsize + 1);

    std::vector<usize> freq(n, 0);
    for (usize r = 0; r != buckets.size(); ++r) {
      bucket_type &b = buckets[r];

      b.rank = std::vector<usize>(rank.begin() + r * bsize,
                                  rank.begin() + std::min(n, (r + 1) * bsize));
      const usize m = b.rank.size();

      {
        b.sorted_ind = std::vector<usize>(m);
        std::iota(b.sorted_ind.begin(), b.sorted_ind.end(),
                  static_cast<usize>(0));
        std::sort(b.sorted_ind.begin(), b.sorted_ind.end(),
                  [&b](const usize l, const usize r) {
                    return b.rank[l] < b.rank[r];
                  });
      }

      {
        b.freq = std::vector<usize>(n + 1);
        b.freq[0] = 0;
        for (usize i = 0; i != n; ++i) {
          b.freq[i + 1] = b.freq[i] + freq[i];
        }
        for (const usize e : b.rank) {
          ++freq[e];
        }
      }

      {
        b.prefix_inv = std::vector<u64>(m);
        u64 inv = 0;
        for (usize i = 0; i != m; ++i) {
          b.prefix_inv[i] = inv;
          for (usize j = 0; j != i; ++j) {
            if (b.rank[j] > b.rank[i]) {
              ++inv;
            }
          }
        }

        if (r + 1 == buckets.size()) {
          b.prefix_inv.push_back(inv);
        } else {
          buckets[r + 1].block_inv = std::vector<u64>(r + 1);
          buckets[r + 1].block_inv[r] = inv;
          for (usize l = r; l != 0;) {
            --l;
            const bucket_type &a = buckets[l];
            usize ri = 0;
            for (const usize i : a.sorted_ind) {
              while (ri != b.sorted_ind.size() &&
                     b.rank[b.sorted_ind[ri]] < a.rank[i]) {
                ++ri;
              }
              inv += ri;
            }
            buckets[r + 1].block_inv[l] = b.block_inv[l] + inv;
          }
        }
      }
    }
  }

  u64 inversions(const usize first, const usize last) const {
    const usize fq = first / bsize;
    const usize fr = first % bsize;
    const usize lq = last / bsize;
    const usize lr = last % bsize;
    const bucket_type &fb = buckets[fq];
    const bucket_type &lb = buckets[lq];

    if (fq == lq) {
      u64 ret = fb.prefix_inv[lr] - fb.prefix_inv[fr];
      usize sum = 0;
      for (const usize i : fb.sorted_ind) {
        if (i < fr) {
          ret -= sum;
        } else if (i < lr) {
          ++sum;
        }
      }
      return ret;
    } else {
      u64 ret = lb.block_inv[fq];
      for (usize i = 0; i != fr; ++i) {
        ret -= lb.freq[fb.rank[i]] - fb.freq[fb.rank[i]];
      }
      ret += static_cast<u64>(fr) * (fr - 1) / 2;
      ret -= fb.prefix_inv[fr];
      ret += lb.prefix_inv[lr];
      ret += static_cast<u64>(lq - fq) * bsize * lr;
      for (usize i = 0; i != lr; ++i) {
        ret -= lb.freq[lb.rank[i]] - fb.freq[lb.rank[i]];
      }
      {
        usize sum = 0;
        auto itr = lb.sorted_ind.begin();
        const auto end = lb.sorted_ind.end();
        for (const usize i : fb.sorted_ind) {
          while (itr != end && lb.rank[*itr] < fb.rank[i]) {
            if (*itr < lr) {
              ++sum;
            }
            ++itr;
          }
          if (i < fr) {
            ret -= sum;
          }
        }
      }
      return ret;
    }
  }
};

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
  int n, q;
  std::scanf("%d%d", &n, &q);
  std::vector<int> v(n);
  for (auto &e : v) {
    std::scanf("%d", &e);
  }
  const auto riq = [&]() {
    std::vector<std::size_t> a(n), c(n);
    std::iota(a.begin(), a.end(), 0);
    std::stable_sort(a.begin(), a.end(),
                     [&](auto l, auto r) { return v[l] < v[r]; });
    for (int i = 0; i != n; ++i) {
      c[a[i]] = i;
    }
    return range_inversions_query(c);
  }();

  for (int i = 0; i != q; ++i) {
    int l, r;
    std::scanf("%d%d", &l, &r);
    std::printf("%lld\n", (long long)riq.inversions(l, r));
  }

  return 0;
}
