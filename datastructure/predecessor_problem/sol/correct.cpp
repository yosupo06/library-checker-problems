// 64-ary tree(top-down)
// O(N + Q log_64 N)

#include <array>
#include <cassert>
#include <string>
#include <type_traits>
using namespace std;

namespace w_ary_tree_impl {
using u64 = uint64_t;
static constexpr unsigned int lgW = 6;
static constexpr unsigned int W = 1u << lgW;
static constexpr int inf = 1 << 30;
inline int ctz(u64 n) { return n ? __builtin_ctzll(n) : -1; }
inline int clz(u64 n) { return n ? 63 - __builtin_clzll(n) : -1; }

template <int LOG, class D = void>
struct w_ary_tree_node {
  u64 map;
  int mn, mx;
  static constexpr int shift = (LOG - 1) * lgW;
  array<w_ary_tree_node<LOG - 1>, W> chd;
  inline int mask(u64 key) const { return key & ((1 << shift) - 1); }

  w_ary_tree_node() : map(0), mn(inf), mx(-1) {}
  void insert(int key) {
    mn = std::min(mn, key), mx = std::max(mx, key);
    int pos = key >> shift;
    map |= 1ULL << pos;
    chd[pos].insert(mask(key));
  }
  void erase(int key) {
    int pos = key >> shift;
    chd[pos].erase(mask(key));
    if (chd[pos].map == 0) map &= ~(1ULL << pos);
    if (mn == mx) {
      mn = inf, mx = -1;
    } else if (mn == key) {
      int p = ctz(map);
      mn = (p << shift) + chd[p].min();
    } else if (mx == key) {
      int p = clz(map);
      mx = (p << shift) + chd[p].max();
    }
  }
  bool contain(int key) const {
    int pos = key >> shift;
    return chd[pos].contain(mask(key));
  }
  inline int min() const { return mn == inf ? -1 : mn; }
  inline int max() const { return mx; }
  int find_next(int key) const {
    if (key <= min()) return min();
    int pos = key >> shift;
    if (((map >> pos) & 1) && mask(key) <= chd[pos].max()) {
      return (pos << shift) + chd[pos].find_next(mask(key));
    }
    int nxt = ctz(map & ~((1ULL << (pos + 1)) - 1));
    if (pos == 63 || nxt == -1) return -1;
    return (nxt << shift) + chd[nxt].min();
  }
  int find_prev(int key) const {
    if (max() < key) return max();
    int pos = key >> shift;
    if (((map >> pos) & 1) && chd[pos].min() < mask(key)) {
      return (pos << shift) + chd[pos].find_prev(mask(key));
    }
    int nxt = clz(map & ((1ULL << pos) - 1ULL));
    if (nxt == -1) return -1;
    return (nxt << shift) + chd[nxt].max();
  }
};

template <int LOG>
struct w_ary_tree_node<LOG, typename std::enable_if<LOG == 1>::type> {
  u64 map;
  w_ary_tree_node() : map(0) {}
  void insert(int key) { map |= 1ULL << key; }
  void erase(int key) { map &= ~(1ULL << key); }
  bool contain(int key) const { return (map >> key) & 1; }
  int min() const { return ctz(map); }
  int max() const { return clz(map); }
  int find_next(int key) const { return ctz(map & ~((1ULL << key) - 1)); }
  int find_prev(int key) const { return clz(map & ((1ULL << key) - 1)); }
};

}  // namespace w_ary_tree_impl

template <int LOG = 4>
using w_ary_tree = w_ary_tree_impl::w_ary_tree_node<LOG>;

w_ary_tree<> set;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  char c = getchar();
  for (int i = 0; i < N; i++) {
    c = getchar();
    if (c == '1') set.insert(i);
  }

  while (Q--) {
    int c, k;
    scanf("%d %d\n", &c, &k);
    if (c == 0) {
      set.insert(k);
    } else if (c == 1) {
      set.erase(k);
    } else if (c == 2) {
      printf("%d\n", set.contain(k));
    } else if (c == 3) {
      printf("%d\n", set.find_next(k));
    } else if (c == 4) {
      printf("%d\n", set.find_prev(k + 1));
    }
  }
}
