#include <cstdio>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges.insert(make_pair(a, b));
        edges.insert(make_pair(b, a));
    }
    vector<int> cc(n, -1);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (cc[i] != -1) {
            continue;
        }
        queue<int> que;
        cc[i] = cnt;
        que.push(i);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u = 0; u < n; ++u) {
                if (!edges.count(make_pair(u, v)) && cc[u] == -1) {
                    cc[u] = cnt;
                    que.push(u);
                }
            }
        }
        ++cnt;
    }
    vector<vector<int>> comps(cnt);
    for (int i = 0; i < n; ++i) {
        comps[cc[i]].push_back(i);
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
