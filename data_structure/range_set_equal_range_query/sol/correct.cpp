#include <vector>
#include <cstdlib>
#include <cstdio>
#include <tuple>
#include <cassert>
#include <cstdint>

using namespace std;

using ll = long long;
using u32 = uint32_t;
using u64 = uint64_t;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

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

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

// 64-ary tree
// space: (N/63) * u64
struct FastSet {
  static constexpr u32 B = 64;
  int n, log;
  vvc<u64> seg;

  FastSet() {}
  FastSet(int n) { build(n); }

  int size() { return n; }

  void build(int m) {
    seg.clear();
    n = m;
    do {
      seg.push_back(vc<u64>((m + B - 1) / B));
      m = (m + B - 1) / B;
    } while (m > 1);
    log = seg.size();
  }
  bool operator[](int i) const { return seg[0][i / B] >> (i % B) & 1; }
  void insert(int i) {
    assert(0 <= i && i < n);
    for (int h = 0; h < log; h++) { seg[h][i / B] |= u64(1) << (i % B), i /= B; }
  }
  void add(int i) { insert(i); }
  void erase(int i) {
    assert(0 <= i && i < n);
    u64 x = 0;
    for (int h = 0; h < log; h++) {
      seg[h][i / B] &= ~(u64(1) << (i % B));
      seg[h][i / B] |= x << (i % B);
      x = bool(seg[h][i / B]);
      i /= B;
    }
  }
  void remove(int i) { erase(i); }

  // min[x,n) or n
  int next(int i) {
    assert(i <= n);
    i = max(i, 0);
    for (int h = 0; h < log; h++) {
      if (i / B == seg[h].size()) break;
      u64 d = seg[h][i / B] >> (i % B);
      if (!d) {
        i = i / B + 1;
        continue;
      }
      i += lowbit(d);
      for (int g = h - 1; g >= 0; g--) {
        i *= B;
        i += lowbit(seg[g][i / B]);
      }
      return i;
    }
    return n;
  }

  // max [0,x], or -1
  int prev(int i) {
    assert(i >= -1);
    if (i >= n) i = n - 1;
    for (int h = 0; h < log; h++) {
      if (i == -1) break;
      u64 d = seg[h][i / B] << (63 - i % B);
      if (!d) {
        i = i / B - 1;
        continue;
      }
      i -= __builtin_clzll(d);
      for (int g = h - 1; g >= 0; g--) {
        i *= B;
        i += topbit(seg[g][i / B]);
      }
      return i;
    }
    return -1;
  }
};

template <typename T>
struct Intervals_Fast {
  const int LLIM, RLIM;
  const T none_val;
  // none_val でない区間の個数と長さ合計
  int total_num;
  int total_len;
  vc<T> dat;
  FastSet ss;

  Intervals_Fast(int N, T none_val) : LLIM(0), RLIM(N), none_val(none_val), total_num(0), total_len(0), dat(N, none_val), ss(N) { ss.insert(0); }

  // x を含む区間の情報の取得 l, r, t
  tuple<int, int, T> get(int x, bool ERASE = false) {
    int l = ss.prev(x);
    int r = ss.next(x + 1);
    T t = dat[l];
    if (t != none_val && ERASE) {
      --total_num, total_len -= r - l;
      dat[l] = none_val;
      merge_at(l);
      merge_at(r);
    }
    return {l, r, t};
  }

  void erase_range(int L, int R) {
    assert(LLIM <= L && L <= R && R <= RLIM);
    if (L == R) return;
    // 半端なところの分割
    int p = ss.prev(L);
    if (p < L) {
      ss.insert(L);
      dat[L] = dat[p];
      if (dat[L] != none_val) ++total_num;
    }
    p = ss.next(R);
    if (R < p) {
      dat[R] = dat[ss.prev(R)];
      ss.insert(R);
      if (dat[R] != none_val) ++total_num;
    }
    p = L;
    while (p < R) {
      int q = ss.next(p + 1);
      if (dat[p] != none_val) --total_num, total_len -= q - p;
      ss.erase(p);
      p = q;
    }
    ss.insert(L);
    dat[L] = none_val;
  }

  void set(int L, int R, T t) {
    if (L == R) return;
    erase_range(L, R);
    ss.insert(L);
    dat[L] = t;
    if (t != none_val) total_num++, total_len += R - L;
    merge_at(L);
    merge_at(R);
  }

  void merge_at(int p) {
    if (p <= 0 || RLIM <= p) return;
    int q = ss.prev(p - 1);
    if (dat[p] == dat[q]) {
      if (dat[p] != none_val) --total_num;
      ss.erase(p);
    }
  }
};

int rd() {
  int x;
  scanf("%d", &x);
  return x;
};

void solve() {
  int N = rd(), Q = rd();
  Intervals_Fast<int> X(N, -1);
  FOR(i, N) {
    int x = rd();
    X.set(i, i + 1, x);
  }
  FOR(Q) {
    int t = rd();
    if (t == 0) {
      int l = rd(), r = rd(), x = rd();
      X.set(l, r, x);
    }
    if (t == 1) {
      int i = rd();
      auto [l, r, x] = X.get(i);
      printf("%d %d %d\n", x, l, r);
    }
  }
}

signed main() { solve(); }
