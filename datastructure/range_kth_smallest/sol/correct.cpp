#include <cstddef>
#include <cstdint>

std::size_t popcount64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return __builtin_popcountll(x);
#else
  x -= x >> 1 & 0x5555555555555555;
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
  return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}

#include <cstddef>
#include <limits>
#include <vector>

class bit_vector {
  using size_t = std::size_t;

  static constexpr size_t wordsize = std::numeric_limits<size_t>::digits;

  class node_type {
  public:
    size_t bit;
    size_t sum;

    node_type() : bit(0), sum(0) {}
  };

  std::vector<node_type> v;

public:
  bit_vector() = default;
  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1) {
    {
      const size_t s = a.size();
      for (size_t i = 0; i != s; i += 1)
        v[i / wordsize].bit |= static_cast<size_t>(a[i] ? 1 : 0)
                               << i % wordsize;
    }
    {
      const size_t s = v.size();
      for (size_t i = 1; i != s; i += 1)
        v[i].sum = v[i - 1].sum + popcount64(v[i - 1].bit);
    }
  }

  size_t rank0(const size_t index) const { return index - rank1(index); }
  size_t rank1(const size_t index) const {
    return v[index / wordsize].sum +
           popcount64(v[index / wordsize].bit &
                      ~(~static_cast<size_t>(0) << index % wordsize));
  }
};

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <class Key> class wavelet_matrix {
  using size_t = std::size_t;

public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

private:
  static bool test(const key_type x, const size_t k) {
    return (x & static_cast<key_type>(1) << k) != 0;
  }
  static void set(key_type &x, const size_t k) {
    x |= static_cast<key_type>(1) << k;
  }

  size_t size_;
  std::vector<bit_vector> mat;

public:
  wavelet_matrix() = default;
  explicit wavelet_matrix(const size_t bit_length, std::vector<key_type> a)
      : size_(a.size()), mat(bit_length, bit_vector()) {
    const size_t s = size();
    for (size_t p = bit_length; p != 0;) {
      p -= 1;
      {
        std::vector<bool> t(s);
        for (size_t i = 0; i != s; i += 1)
          t[i] = test(a[i], p);
        mat[p] = bit_vector(t);
      }
      {
        std::vector<key_type> v0, v1;
        for (const size_t e : a)
          (test(e, p) ? v1 : v0).push_back(e);
        const auto itr = std::copy(v0.cbegin(), v0.cend(), a.begin());
        std::copy(v1.cbegin(), v1.cend(), itr);
      }
    }
  }

  size_t size() const { return size_; }

  key_type quantile(size_t first, size_t last, size_t k) const {
    assert(first <= last);
    assert(last <= size());
    assert(k < last - first);

    key_type ret = 0;
    for (size_t p = mat.size(); p != 0;) {
      p -= 1;
      const bit_vector &v = mat[p];
      const size_t z = v.rank0(last) - v.rank0(first);
      if (k < z) {
        first = v.rank0(first);
        last = v.rank0(last);
      } else {
        set(ret, p);
        k -= z;
        const size_t b = v.rank0(size());
        first = b + v.rank1(first);
        last = b + v.rank1(last);
      }
    }
    return ret;
  }
};

#include <iostream>
#include <vector>

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int &e : a)
    std::cin >> e;
  const wavelet_matrix<int> wm(30, a);
  for (int i = 0; i != q; i += 1) {
    int l, r, k;
    std::cin >> l >> r >> k;
    std::cout << wm.quantile(l, r, k) << std::endl;
  }
}
