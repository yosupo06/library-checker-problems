#include <cstring>
#include <string>
#include <cstdio>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

using ll = long long;

template <class T>
using vc = vector<T>;

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
#define mp make_pair
#define fi first
#define se second

// sigma が小さい
// 一般の n 頂点の木構造で O(n) 時間で動く
template <int sigma>
struct Trie {
  struct Node {
    array<int, sigma> ch;
    array<int, sigma> nxt; // suffix link -> add c
    int parent;
    int suffix_link;
  };
  int n_node;
  vc<Node> nodes;
  vc<int> words;
  vc<int> BFS; // BFS 順

  Trie() {
    n_node = 0;
    new_node();
  }

  Node &operator[](int i) { return nodes[i]; }

  template <typename STRING>
  int add(STRING S, int off) {
    int v = 0;
    for (auto &&s: S) { v = add_single(v, s, off); }
    words.eb(v);
    return v;
  }

  int add_single(int v, int c, int off) {
    c -= off;
    assert(0 <= c && c < sigma);
    if (nodes[v].ch[c] != -1) return nodes[v].ch[c];
    nodes[v].ch[c] = new_node();
    nodes.back().parent = v;
    return nodes[v].ch[c];
  }

  void calc_suffix_link() {
    BFS.resize(n_node);
    int p = 0, q = 0;
    BFS[q++] = 0;
    fill(all(nodes[0].nxt), 0);
    while (p < q) {
      int v = BFS[p++];
      if (v) nodes[v].nxt = nodes[nodes[v].suffix_link].nxt;
      FOR(s, sigma) {
        int w = nodes[v].ch[s];
        if (w == -1) continue;
        nodes[w].suffix_link = nodes[v].nxt[s];
        nodes[v].nxt[s] = w;
        BFS[q++] = w;
      }
    }
  }

  vc<int> calc_count() {
    vc<int> count(n_node);
    for (auto &&x: words) count[x]++;
    for (auto &&v: BFS)
      if (v) { count[v] += count[nodes[v].suffix_link]; }
    return count;
  }

private:
  int new_node() {
    Node c;
    fill(all(c.ch), -1);
    fill(all(c.nxt), -1);
    c.parent = -1;
    c.suffix_link = -1;
    nodes.eb(c);
    return n_node++;
  }
};

void solve() {
  int N;
  scanf("%d", &N);
  static char buf[1'000'100];
  Trie<26> trie;
  FOR(N) {
    scanf("%s", buf);
    string S;
    S = buf;
    trie.add(S, 'a');
  }
  int n = trie.n_node;
  trie.calc_suffix_link();

  printf("%d\n", n);
  FOR(v, 1, n) printf("%d %d\n", trie[v].parent, trie[v].suffix_link);

  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    printf("%d", trie.words[i]);
  }
  printf("\n");
}

signed main() { solve(); }
