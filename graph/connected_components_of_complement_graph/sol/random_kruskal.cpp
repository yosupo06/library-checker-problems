#include <cstdio>
#include <queue>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

struct UnionFind {
  vector<int> pa, rk;
  UnionFind(int n) : pa(n), rk(n) {
    for (int i = 0; i < n; i++)
      pa[i] = i;
  }
  int anc(int x) {
    return x==pa[x] ? x : pa[x]=anc(pa[x]);
  }
  bool join(int x, int y) {
    x = anc(x);
    y = anc(y);
    if (x == y) return false;
    if (rk[x] < rk[y]) swap(x, y);
    pa[y] = x;
    if (rk[x] == rk[y]) ++rk[x];
    return true;
  }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges.push_back(minmax(a, b));
    }
    mt19937 rng(0x9a073a8cf511901c);

    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int cnt = n;
    int t = 1e7;
    while (cnt > 1 && t--) {
      int a = uniform_int_distribution<int>(0, n - 1)(rng);
      int b = uniform_int_distribution<int>(0, n - 1)(rng);
      pair<int, int> e = minmax(a, b);
      if (not binary_search(edges.begin(), edges.end(), e)) {
        if (uf.join(a, b))
          --cnt;
      }
    }

    vector<int> id(n, -1);
    for (int i = 0, l = 0; i < n; i++)
      if (id[uf.anc(i)] == -1)
        id[uf.anc(i)] = l++;

    vector<vector<int>> comps(cnt);
    for (int i = 0; i < n; ++i) {
        comps[id[uf.anc(i)]].push_back(i);
    }
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) {
        printf("%d", (int)comps[i].size());
        for (int u : comps[i]) {
            printf(" %d", u);
        }
        printf("\n");
    }
}
