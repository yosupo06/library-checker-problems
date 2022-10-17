#include <vector>
#include <utility>
#include <stdint.h>
#include "testlib.h"

using namespace std;

template <typename T>
using vc = vector<T>;

#define eb emplace_back

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int N = inf.readInt();
  int M = inf.readInt();
  using P = pair<int, int>;
  vc<P> edges;
  for (int i = 0; i < M; ++i) {
    int a = inf.readInt();
    int b = inf.readInt();
    edges.eb(a, b);
  }

  int L_ans = ans.readInt();
  int L = ouf.readInt(-1, N);
  if (L == -1) {
    if (L_ans == -1) quitf(_ok, "OK");
    quitf(_wa, "cycle exists, but ouf dont find it");
  }

  if (L <= 0) quitf(_wa, "L must be positive");

  vc<int> V(L), E(L);
  for (int i = 0; i < L; ++i) { V[i] = ouf.readInt(0, N - 1); }
  for (int i = 0; i < L; ++i) { E[i] = ouf.readInt(0, M - 1); }

  vc<int> used_v(N), used_e(M);
  for (auto&& v: V) {
    if (used_v[v]) { quitf(_wa, "vi=vj"); }
    used_v[v] = 1;
  }
  for (auto&& e: E) {
    if (used_e[e]) { quitf(_wa, "ei=ej"); }
    used_e[e] = 1;
  }
  for (int i = 0; i < L; ++i) {
    auto [a, b] = edges[E[i]];
    int j = (i + 1 == L ? 0 : i + 1);
    bool ok = 0;
    if (V[i] == a && V[j] == b) ok = 1;
    if (V[i] == b && V[j] == a) ok = 1;
    if (!ok) quitf(_wa, "ei does not connect vi and vi+1");
  }

  quitf(_ok, "OK");
  return 0;
}
