#include <vector>

#include "params.h"
#include "testlib.h"

// begin   <atcoder/dsu>

#include <algorithm>
#include <cassert>
#include <vector>

namespace atcoder {

// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct dsu {
 public:
  dsu() : _n(0) {}
  explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

  int merge(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    int x = leader(a), y = leader(b);
    if (x == y) return x;
    if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    return x;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return leader(a) == leader(b);
  }

  int leader(int a) {
    assert(0 <= a && a < _n);
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = leader(parent_or_size[a]);
  }

  int size(int a) {
    assert(0 <= a && a < _n);
    return -parent_or_size[leader(a)];
  }

  std::vector<std::vector<int>> groups() {
    std::vector<int> leader_buf(_n), group_size(_n);
    for (int i = 0; i < _n; i++) {
      leader_buf[i] = leader(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> result(_n);
    for (int i = 0; i < _n; i++) {
      result[i].reserve(group_size[i]);
    }
    for (int i = 0; i < _n; i++) {
      result[leader_buf[i]].push_back(i);
    }
    result.erase(
        std::remove_if(result.begin(), result.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        result.end());
    return result;
  }

 private:
  int _n;
  // root node: -1 * component size
  // otherwise: parent
  std::vector<int> parent_or_size;
};

}  // namespace atcoder

// end    <atcoder/dsu>

using lint = long long int;

int main() {
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readChar(' ');
  int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  for (int i = 0; i < N; i++) {
    if (i != 0) inf.readChar(' ');
    inf.readInt(A_MIN, MOD - 1);
  }
  inf.readChar('\n');

  std::vector<int> U(N - 1), V(N - 1);

  for (int i = 0; i < N - 1; i++) {
    U[i] = inf.readInt(0, N - 1);
    inf.readChar(' ');
    V[i] = inf.readInt(0, N - 1);
    inf.readChar(' ');
    inf.readInt(B_MIN, MOD - 1);
    inf.readChar(' ');
    inf.readInt(C_MIN, MOD - 1);
    inf.readChar('\n');
  }

  for (int i = 0; i < Q; i++) {
    int cmd = inf.readInt(0, 1);
    inf.readChar(' ');
    if (cmd == 0) {
      inf.readInt(0, N - 1);
      inf.readChar(' ');
      inf.readInt(A_MIN, MOD - 1);
      inf.readChar(' ');
      inf.readInt(0, N - 1);
      inf.readChar('\n');
    } else {
      inf.readInt(0, N - 2);
      inf.readChar(' ');
      inf.readInt(B_MIN, MOD - 1);
      inf.readChar(' ');
      inf.readInt(C_MIN, MOD - 1);
      inf.readChar(' ');
      inf.readInt(0, N - 1);
      inf.readChar('\n');
    }
  }

  // check connectivity
  atcoder::dsu dsu(N);
  for (int i = 0; i < N - 1; i++) {
    ensure(!dsu.same(U[i], V[i]));
    dsu.merge(U[i], V[i]);
  }

  inf.readEof();
  return 0;
}
