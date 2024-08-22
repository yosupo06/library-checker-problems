/* 64分木。
insert, erase
[]での存在判定
next, prev
*/
struct FastSet {
  using uint = unsigned;
  using ull = unsigned long long;

  int bsr(ull x) { return 63 - __builtin_clzll(x); }
  int bsf(ull x) { return __builtin_ctzll(x); }

  static constexpr uint B = 64;
  int n, lg;
  vector<vector<ull>> seg;
  FastSet(int _n) : n(_n) {
    do {
      seg.push_back(vector<ull>((_n + B - 1) / B));
      _n = (_n + B - 1) / B;
    } while (_n > 1);
    lg = int(seg.size());
  }
  bool operator[](int i) const { return (seg[0][i / B] >> (i % B) & 1) != 0; }
  void insert(int i) {
    for (int h = 0; h < lg; h++) {
      seg[h][i / B] |= 1ULL << (i % B);
      i /= B;
    }
  }
  void erase(int i) {
    for (int h = 0; h < lg; h++) {
      seg[h][i / B] &= ~(1ULL << (i % B));
      if (seg[h][i / B]) break;
      i /= B;
    }
  }

  // x以上最小の要素を返す。存在しなければ n。
  int next(int i) {
    for (int h = 0; h < lg; h++) {
      if (i / B == seg[h].size()) break;
      ull d = seg[h][i / B] >> (i % B);
      if (!d) {
        i = i / B + 1;
        continue;
      }
      // find
      i += bsf(d);
      for (int g = h - 1; g >= 0; g--) {
        i *= B;
        i += bsf(seg[g][i / B]);
      }
      return i;
    }
    return n;
  }

  // x以下最大の要素を返す。存在しなければ -1。
  int prev(int i) {
    if (i < 0) return -1;
    if (i >= n) i = n - 1;
    for (int h = 0; h < lg; h++) {
      if (i == -1) break;
      ull d = seg[h][i / B] << (63 - i % 64);
      if (!d) {
        i = i / B - 1;
        continue;
      }
      // find
      i += bsr(d) - (B - 1);
      for (int g = h - 1; g >= 0; g--) {
        i *= B;
        i += bsr(seg[g][i / B]);
      }
      return i;
    }
    return -1;
  }

  // [l, r) 内の要素を全部集める
  vector<int> collect(int l, int r) {
    vector<int> res;
    int x = l - 1;
    while (1) {
      x = next(x + 1);
      if (x >= r) break;
      res.emplace_back(x);
    }
    return res;
  }
};
