#include <cstdio>
#include <vector>
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

  vector<int> key(N);
  vector<X> dat(N);
  for (int n = 0; n < N; ++n) {
    int p, a, b;
    scanf("%d %d %d", &p, &a, &b);
    key[n] = p;
    dat[n] = {mint(a), mint(b)};
  }

  Sortable_SegTree<Mono> seg(key, dat);

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, a, b;
      scanf("%d %d %d", &i, &a, &b);
      seg.set(i, {mint(a), mint(b)});
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      auto f = seg.prod(l, r);
      mint ans = Mono::eval(f, mint(x));
      printf("%d\n", ans.val);
    }
    if (t == 2) {
      int l, r;
      scanf("%d %d", &l, &r);
      seg.sort_inc(l, r);
    }
    if (t == 3) {
      int l, r;
      scanf("%d %d", &l, &r);
      seg.sort_dec(l, r);
    }
  }

  return 0;
}
