
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "../params.h"
#include "query.h"
#include "random.h"

struct Tree {
  int n = 1;
  std::vector<std::pair<int, int>> edges;

  void shuffle_nodes(Random& rng) {
    auto perm = rng.perm<int>(n);
    for (auto& e : edges) {
      e.first = perm[e.first];
      e.second = perm[e.second];
    }
  }
  void shuffle_edges(Random& rng, bool can_flip = true) {
    rng.shuffle(edges.begin(), edges.end());
    if (can_flip) {
      for (auto& e : edges) {
        if (rng.uniform_bool()) std::swap(e.first, e.second);
      }
    }
  }

  void push(int u, int v) { edges.emplace_back(u, v); }

  void expand_random_edges(Random& rng, int count) {
    assert(n >= 2);
    int fixn = n;
    for (int i = 0; i < count; i++) {
      int e = rng.uniform(0, fixn - 2);
      push(edges[e].first, n);
      edges[e].first = n;
      n++;
    }
  }

  void join_random_edges(Random& rng, int count) {
    int fixn = n;
    for (int i = 0; i < count; i++) {
      push(rng.uniform(0, fixn - 1), n);
      n++;
    }
  }

  void toCentipede() {
    int fixn = n;
    for (int i = 0; i < fixn; i++) {
      push(i, n);
      n++;
    }
  }

  static Tree Line(int n) {
    Tree res;
    res.n = n;
    for (int i = 0; i < n - 1; i++) res.push(i, i + 1);
    return res;
  }

  static Tree Star(int n) {
    Tree res;
    res.n = n;
    for (int i = 0; i < n - 1; i++) res.push(0, i + 1);
    return res;
  }

  static Tree KLines(int n, int k) {
    assert(3 <= k);
    Tree res;
    res.n = n;
    for (int i = 1; i < n; i++) res.push(std::max(0, i - k), i);
    return res;
  }

  static Tree KAry(int n, int k) {
    assert(2 <= k);
    Tree res;
    res.n = n;
    for (int i = 0; i < n - 1; i++) res.push(i / k, i + 1);
    return res;
  }

  static Tree Broom(int n, int line_length) {
    assert(line_length <= n);
    Tree res;
    res.n = n;
    for (int i = 0; i < line_length; i++) res.push(i, i + 1);
    for (int i = line_length; i < n - 1; i++) res.push(line_length - 1, i + 1);
    return res;
  }

  static Tree LongestPathDecompositionKiller(int n) {
    assert(n >= 10);
    Tree res;
    res.n = n;
    std::vector<int> rt;
    int now_n = 0;
    for (int len = 1;; len += 2) {
      if (now_n + len > n) break;
      for (int i = 0; i < len - 1; i++) {
        res.push(now_n + i, now_n + i + 1);
      }
      rt.push_back(now_n);
      now_n += len;
    }
    for (int i = 0; i + 1 < (int)rt.size(); i++) {
      res.push(rt[i], rt[i + 1]);
    }
    for (int i = now_n; i < n; i++) {
      res.push(i - 1, i);
    }
    return res;
  }

  static Tree GenerateByTemplateId(Random& rng, int id, int n) {
    assert(n >= 10);
    assert(id >= 0);
    if (id-- == 0) return Line(n);
    if (id-- == 0) return Star(n);
    if (id-- == 0) return KAry(n, 2);
    if (id-- == 0) return LongestPathDecompositionKiller(n);
    if (id-- == 0) {
      auto res = Line(n / 2);
      res.toCentipede();
      res.join_random_edges(rng, n % 2);
      return res;
    }
    if (id-- == 0) return Broom(n, (long long)n * 2 / 5);
    if (id-- == 0) return Broom(n, (long long)n * 3 / 5);
    if (id-- == 0) return KLines(n, 3);
    if (id-- == 0) return KAry(n, 3);
    if (id-- == 0) {
      auto res = Star(n / 2);
      res.expand_random_edges(rng, n / 2);
      return res;
    }
    assert(false);
  }
};

int main(int, char* argv[]) {
  int id = (int)atoll(argv[1]);
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int Q = Q_MAX;

  Tree tree = Tree::GenerateByTemplateId(gen, id, N);
  tree.shuffle_edges(gen);
  tree.shuffle_nodes(gen);

  std::vector<int> A(N), B(N - 1), C(N - 1);
  for (int i = 0; i < N; i++) A[i] = gen.uniform(A_MIN, MOD - 1);
  for (int i = 0; i < N - 1; i++) B[i] = gen.uniform(B_MIN, MOD - 1);
  for (int i = 0; i < N - 1; i++) C[i] = gen.uniform(C_MIN, MOD - 1);

  printf("%d %d\n", N, Q);

  for (int i = 0; i < N; i++) {
    if (i) printf(" ");
    printf("%d", A[i]);
  }
  printf("\n");

  for (int i = 0; i < N - 1; i++) {
    printf("%d %d %d %d\n", tree.edges[i].first, tree.edges[i].second, B[i],
           C[i]);
  }

  QueryData qd{N, Q, gen};
  qd.print();
  return 0;
}
