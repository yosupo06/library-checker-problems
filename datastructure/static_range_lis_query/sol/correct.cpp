/*

References

[1]   Tiskin, A. (2008).Semi-local string comparison: Algorithmic techniques
      and applications. Mathematics in Computer Science, 1(4), 571-603.

[2]   Claude, F., Navarro, G., & Ordónez, A. (2015). The wavelet matrix: An
      efficient wavelet tree for large alphabets. Information Systems, 47,
      15-32.

*/

// #pragma GCC target("popcnt")

#include <algorithm>
#include <cassert>
#include <climits>
#include <numeric>
#include <utility>
#include <vector>

namespace noshi91 {

namespace range_lis_query_impl {

namespace wavelet_matrix_impl {

using uint = unsigned int;
using ll = long long;

static constexpr int w = CHAR_BIT * sizeof(uint);

int popcount(uint x) {
#ifdef __GNUC__
  return __builtin_popcount(x);
#else
  static_assert(w == 32, "");
  x -= x >> 1 & 0x55555555;
  x = (x & 0x33333333) + (x >> 2 & 0x33333333);
  x = x + (x >> 4) & 0x0F0F0F0F;
  return x * 0x01010101 >> 24 & 0x3F;
#endif
}

class bit_vector {
  class node_type {
  public:
    uint bit;
    int sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector(const uint n) : v(n / w + 1) {}

  void set(const uint i) {
    v[i / w].bit |= uint(1) << i;
    v[i / w].sum += 1;
  }

  void build() {
    for (int i = 1; i < int(v.size()); i++) {
      v[i].sum += v[i - 1].sum;
    }
  }

  int rank(const uint i) const {
    return v[i / w].sum - popcount(v[i / w].bit & ~uint(0) << i % w);
  }

  int one() const { return v.back().sum; }
};

class wavelet_matrix {
private:
  template <class I> static bool test(const I x, const int k) {
    return (x & I(1) << k) != I(0);
  }

  std::vector<bit_vector> mat;

public:
  template <class I>
  wavelet_matrix(const int bit_length, std::vector<I> a)
      : mat(bit_length, bit_vector(a.size())) {
    const int n = a.size();
    std::vector<I> a0;
    a0.reserve(n);
    for (int p = bit_length - 1; p >= 0; p--) {
      bit_vector &v = mat[p];
      auto itr = a.begin();
      for (int i = 0; i < n; i++) {
        if (test(a[i], p)) {
          v.set(i);
          *itr = a[i];
          itr++;
        } else {
          a0.push_back(a[i]);
        }
      }
      v.build();
      std::copy(a0.begin(), a0.end(), itr);
      a0.clear();
    }
  }

  int count_less_than(int l, int r, const ll key) const {
    int ret = r - l;
    for (int p = mat.size() - 1; p >= 0; p--) {
      const bit_vector &v = mat[p];
      const int rank_l = v.rank(l);
      const int rank_r = v.rank(r);
      if (test(key, p)) {
        l = rank_l;
        r = rank_r;
      } else {
        ret -= rank_r - rank_l;
        const int o = v.one();
        l += o - rank_l;
        r += o - rank_r;
      }
    }
    return ret - (r - l);
  }
};

} // namespace wavelet_matrix_impl

using wavelet_matrix_impl::wavelet_matrix;

using vi = std::vector<int>;
using iter = typename vi::iterator;

static constexpr int none = -1;

vi inverse(const vi &p) {
  const int n = p.size();
  vi q(n, none);
  for (int i = 0; i < n; i++) {
    if (p[i] != none) {
      q[p[i]] = i;
    }
  }
  return q;
}

void unit_monge_dmul(const int n, iter stack, const iter a, const iter b) {
  if (n == 1) {
    stack[0] = 0;
    return;
  }
  const iter c_row = stack;
  stack += n;
  const iter c_col = stack;
  stack += n;

  const auto map = [=](const int len, const auto f, const auto g) {
    const iter a_h = stack + 0 * len;
    const iter a_m = stack + 1 * len;
    const iter b_h = stack + 2 * len;
    const iter b_m = stack + 3 * len;
    const auto split = [=](const iter v, iter v_h, iter v_m) {
      for (int i = 0; i < n; i++) {
        if (f(v[i])) {
          *v_h = g(v[i]);
          ++v_h;
          *v_m = i;
          ++v_m;
        }
      }
    };
    split(a, a_h, a_m);
    split(b, b_h, b_m);
    const iter c = stack + 4 * len;
    unit_monge_dmul(len, c, a_h, b_h);
    for (int i = 0; i < len; i++) {
      const int row = a_m[i];
      const int col = b_m[c[i]];
      c_row[row] = col;
      c_col[col] = row;
    }
  };
  const int mid = n / 2;
  map(mid, [mid](const int x) { return x < mid; },
      [](const int x) { return x; });
  map(n - mid, [mid](const int x) { return x >= mid; },
      [mid](const int x) { return x - mid; });

  class d_itr {
  public:
    int delta;
    int col;
    d_itr() : delta(0), col(0) {}
  };
  int row = n;
  const auto right = [&](d_itr &it) {
    if (b[it.col] < mid) {
      if (c_col[it.col] >= row) {
        it.delta += 1;
      }
    } else {
      if (c_col[it.col] < row) {
        it.delta += 1;
      }
    }
    it.col += 1;
  };
  const auto up = [&](d_itr &it) {
    if (a[row] < mid) {
      if (c_row[row] >= it.col) {
        it.delta -= 1;
      }
    } else {
      if (c_row[row] < it.col) {
        it.delta -= 1;
      }
    }
  };
  d_itr neg, pos;
  while (row != 0) {
    while (pos.col != n) {
      d_itr temp = pos;
      right(temp);
      if (temp.delta == 0) {
        pos = temp;
      } else {
        break;
      }
    }
    row -= 1;
    up(neg);
    up(pos);
    while (neg.delta != 0) {
      right(neg);
    }
    if (neg.col > pos.col) {
      c_row[row] = pos.col;
    }
  }
}

vi subunit_monge_dmul(vi a, vi b) {
  const int n = a.size();
  vi a_inv = inverse(a);
  vi b_inv = inverse(b);
  std::swap(b, b_inv);
  vi a_map, b_map;
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] != none) {
      a_map.push_back(i);
      a[n - a_map.size()] = a[i];
    }
  }
  std::reverse(a_map.begin(), a_map.end());
  {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (a_inv[i] == none) {
        a[cnt] = i;
        cnt += 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (b[i] != none) {
      b[b_map.size()] = b[i];
      b_map.push_back(i);
    }
  }
  {
    int cnt = b_map.size();
    for (int i = 0; i < n; i++) {
      if (b_inv[i] == none) {
        b[cnt] = i;
        cnt += 1;
      }
    }
  }
  vi c([](int n) {
    int ret = 0;
    while (n > 1) {
      ret += 2 * n;
      n = (n + 1) / 2;
      ret += 4 * n;
    }
    ret += 1;
    return ret;
  }(n));
  unit_monge_dmul(n, c.begin(), a.begin(), b.begin());

  vi c_pad(n, none);
  for (int i = 0; i < int(a_map.size()); i++) {
    const int t = c[n - a_map.size() + i];
    if (t < int(b_map.size())) {
      c_pad[a_map[i]] = b_map[t];
    }
  }
  return c_pad;
}

vi seaweed_doubling(const vi &p) {
  const int n = p.size();
  if (n == 1) {
    return vi({none});
  }
  const int mid = n / 2;
  vi lo, hi;
  vi lo_map, hi_map;
  for (int i = 0; i < n; i++) {
    const int e = p[i];
    if (e < mid) {
      lo.push_back(e);
      lo_map.push_back(i);
    } else {
      hi.push_back(e - mid);
      hi_map.push_back(i);
    }
  }
  lo = seaweed_doubling(lo);
  hi = seaweed_doubling(hi);
  vi lo_pad(n), hi_pad(n);
  std::iota(lo_pad.begin(), lo_pad.end(), 0);
  std::iota(hi_pad.begin(), hi_pad.end(), 0);
  for (int i = 0; i < mid; i++) {
    if (lo[i] == none) {
      lo_pad[lo_map[i]] = none;
    } else {
      lo_pad[lo_map[i]] = lo_map[lo[i]];
    }
  }
  for (int i = 0; mid + i < n; i++) {
    if (hi[i] == none) {
      hi_pad[hi_map[i]] = none;
    } else {
      hi_pad[hi_map[i]] = hi_map[hi[i]];
    }
  }
  return subunit_monge_dmul(std::move(lo_pad), std::move(hi_pad));
}

bool is_permutation(const vi &p) {
  const int n = p.size();
  std::vector<bool> used(n, false);
  for (const int e : p) {
    if (e < 0 || n <= e || used[e]) {
      return false;
    }
    used[e] = true;
  }
  return true;
}

wavelet_matrix convert(const vi &p) {
  assert(is_permutation(p));
  int n = p.size();
  vi row;
  if (n != 0) {
    row = seaweed_doubling(vi(p.begin(), p.end()));
  }
  for (int &e : row) {
    if (e == none) {
      e = n;
    }
  }
  int bit_length = 0;
  while (n > 0) {
    bit_length += 1;
    n /= 2;
  }
  return wavelet_matrix(bit_length, std::move(row));
}

class range_lis_query {
  int n;
  wavelet_matrix wm;

public:
  range_lis_query() : range_lis_query(std::vector<int>()) {}
  explicit range_lis_query(const std::vector<int> &p)
      : n(p.size()), wm(convert(p)) {}

  int query(const int left, const int right) const {
    assert(0 <= left && left <= right && right <= n);
    return (right - left) - wm.count_less_than(left, n, right);
  }
};

} // namespace range_lis_query_impl

using range_lis_query_impl::range_lis_query;

} // namespace noshi91

#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> P(N);
  for (int &p : P) {
    std::cin >> p;
  }

  const noshi91::range_lis_query rlq(P);

  for (int i = 0; i < Q; i++) {
    int l, r;
    std::cin >> l >> r;
    std::cout << rlq.query(l, r) << "\n";
  }

  return 0;
}
