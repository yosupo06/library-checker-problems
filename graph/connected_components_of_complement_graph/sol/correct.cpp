#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> cc(n, -1);
    int cnt = 0;
    vector<int> rem(n);
    for (int i = 0; i < n; ++i) {
        rem[i] = i;
    }
    vector<int> flg(n, 0);
    while (!rem.empty()) {
        int r = rem.back();
        rem.pop_back();
        queue<int> que;
        cc[r] = cnt;
        que.push(r);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u : g[v]) {
                flg[u] = 1;
            }
            vector<int> nxtrem;
            for (int u : rem) {
                if (flg[u]) {
                    nxtrem.push_back(u);
                } else if (cc[u] == -1) {
                    cc[u] = cnt;
                    que.push(u);
                }
            }
            for (int u : g[v]) {
                flg[u] = 0;
            }
            rem = nxtrem;
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
