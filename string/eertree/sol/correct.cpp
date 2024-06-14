#include <vector>
#include <array>
#include <string>
#include <cstdio>
#include <cassert>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

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

#define len(x) ll(x.size())
#define all(x) x.begin(), x.end()
#define elif else if
#define eb emplace_back

template <int sigma>
struct Palindromic_Tree {
  struct Node {
    array<int, sigma> TO;
    int link;
    int length;
    pair<int, int> pos; // position of first ocurrence
    Node(int link, int length, int l, int r)
        : link(link), length(length), pos({l, r}) {
      fill(all(TO), -1);
    }
  };

  vc<Node> nodes;
  vc<int> path;

  template <typename STRING>
  Palindromic_Tree(const STRING &S, char off) {
    nodes.eb(Node(-1, -1, 0, -1));
    nodes.eb(Node(0, 0, 0, 0));
    int p = 0;
    FOR(i, len(S)) {
      path.eb(p);
      int x = S[i] - off;
      while (p) {
        int j = i - 1 - nodes[p].length;
        bool can = (j >= 0 && S[j] - off == x);
        if (!can) {
          p = nodes[p].link;
          continue;
        }
        break;
      }
      if (nodes[p].TO[x] != -1) {
        p = nodes[p].TO[x];
        continue;
      }
      int to = len(nodes);
      int l = i - 1 - nodes[p].length;
      int r = i + 1;
      nodes[p].TO[x] = to;

      int link;
      if (p == 0) link = 1;
      if (p != 0) {
        while (1) {
          p = nodes[p].link;
          int j = i - 1 - nodes[p].length;
          bool can = (j >= 0 && S[j] - off == x);
          if (can) break;
        }
        assert(nodes[p].TO[x] != -1);
        link = nodes[p].TO[x];
      }
      nodes.eb(Node(link, r - l, l, r));
      p = to;
    }
    path.eb(p);
  }

  // node ごとの出現回数
  vc<int> count() {
    vc<int> res(len(nodes));
    for (auto &&p: path) res[p]++;
    FOR_R(k, 1, len(nodes)) {
      int link = nodes[k].link;
      res[link] += res[k];
    }
    return res;
  }
};

void solve() {
  string S;
  static char buf[1'000'100];
  scanf("%s", buf);
  S = buf;

  Palindromic_Tree<26> PT(S, 'a');
  int n = len(PT.nodes);
  vc<int> par(n, -1);
  FOR(i, n) {
    for (auto &t: PT.nodes[i].TO) {
      if (t != -1) par[t] = i;
    }
  }
  printf("%d\n", n - 2);
  FOR(i, 2, n) {
    auto &c = PT.nodes[i];
    printf("%d %d\n", par[i] - 1, c.link - 1);
  }
  auto ANS = PT.path;
  ANS.erase(ANS.begin());
  for (auto &x: ANS) --x;
  for (int i = 0; i < len(ANS); ++i) {
    if (i) printf(" ");
    printf("%d", ANS[i]);
  }
  printf("\n");
}

signed main() {
  solve();
  return 0;
}
