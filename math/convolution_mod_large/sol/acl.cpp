#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

#include "../acl.h"
#include "../fastio.h"

using mint = atcoder::modint998244353;
using vm = vector<mint>;

vm convolution998244353_large(const vm &a, const vm &b) {
  int len = 1 << 23;
  if ((int)a.size() + (int)b.size() - 1 <= len)
    return atcoder::convolution(a, b);
  if (a.empty() || b.empty()) return vm(max<int>(0, a.size() + b.size() - 1));
  vector<vm> as, bs;
  for (int i = 0; i < (int)a.size(); i += len / 2) {
    vm v{begin(a) + i, begin(a) + min<int>(i + len / 2, a.size())};
    v.resize(len);
    atcoder::internal::butterfly(v);
    as.push_back(v);
  }
  for (int i = 0; i < (int)b.size(); i += len / 2) {
    vm v{begin(b) + i, begin(b) + min<int>(i + len / 2, b.size())};
    v.resize(len);
    atcoder::internal::butterfly(v);
    bs.push_back(v);
  }
  vector<vm> cs(as.size() + bs.size() - 1, vm(len));
  for (int i = 0; i < (int)as.size(); i++) {
    for (int j = 0; j < (int)bs.size(); j++) {
      for (int k = 0; k < len; k++) {
        cs[i + j][k] += as[i][k] * bs[j][k];
      }
    }
  }
  for (auto &v : cs) atcoder::internal::butterfly_inv(v);

  vector<mint> c(a.size() + b.size() - 1);
  for (int i = 0; i < (int)cs.size(); i++) {
    int offset = len / 2 * i;
    int je = min<int>(len, c.size() - offset);
    for (int j = 0; j < je; j++) {
      c[j + offset] += cs[i][j];
    }
  }

  mint inv = mint{len}.inv();
  for (auto &x : c) x *= inv;
  return c;
}

int main() {
  int n, m, buf;
  rd(n, m);
  vector<mint> a(n), b(m);
  for (auto &x : a) rd(buf), x = buf;
  for (auto &x : b) rd(buf), x = buf;
  auto c = convolution998244353_large(a, b);
  int nm = n + m - 2;
  for (int i = 0; i <= nm; i++) {
    wt(c[i].val());
    wt(" \n"[i == nm]);
  }
  return 0;
}
