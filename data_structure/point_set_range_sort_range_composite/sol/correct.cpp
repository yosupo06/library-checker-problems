#include <cstdio>
#include <vector>
#include <tuple>
#include <cassert>
#include <algorithm>

using namespace std;

#include "segtree.hpp"
#include "fastset.hpp"
#include "sortable_segtree.hpp"
#include "modint.hpp"
#include "group_affine.hpp"

using mint = modint998;
using Mono = Group_Affine<mint>;
using X = typename Mono::value_type;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> all_key;
  using QT = tuple<int, int, int, int, int>;
  vector<QT> query(Q);

  vector<int> key(N);
  vector<X> dat(N);
  for (int n = 0; n < N; ++n) {
    int p, a, b;
    scanf("%d %d %d", &p, &a, &b);
    key[n] = p;
    dat[n] = {mint(a), mint(b)};
    all_key.emplace_back(p);
  }

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, p, a, b;
      scanf("%d %d %d %d", &i, &p, &a, &b);
      query[q] = {t, i, p, a, b};
      all_key.emplace_back(p);
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      query[q] = {t, l, r, x, 0};
    }
    if (t == 2) {
      int l, r;
      scanf("%d %d", &l, &r);
      query[q] = {t, l, r, 0, 0};
    }
    if (t == 3) {
      int l, r;
      scanf("%d %d", &l, &r);
      query[q] = {t, l, r, 0, 0};
    }
  }

  sort(all_key.begin(), all_key.end());
  for (auto&& x: key)
    x = lower_bound(all_key.begin(), all_key.end(), x) - all_key.begin();

  Sortable_SegTree<Mono> seg(all_key.size(), key, dat);

  for (int q = 0; q < Q; ++q) {
    auto [t, x1, x2, x3, x4] = query[q];
    if (t == 0) {
      int i = x1;
      int p = lower_bound(all_key.begin(), all_key.end(), x2) - all_key.begin();
      int a = x3;
      int b = x4;
      seg.set(i, p, {mint(a), mint(b)});
    }
    if (t == 1) {
      int l = x1, r = x2, x = x3;
      auto f = seg.prod(l, r);
      mint ans = Mono::eval(f, mint(x));
      printf("%d\n", ans.val);
    }
    if (t == 2) {
      int l = x1, r = x2;
      seg.sort_inc(l, r);
    }
    if (t == 3) {
      int l = x1, r = x2;
      seg.sort_dec(l, r);
    }
  }

  return 0;
}
