#include <stdio.h>
#include <vector>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<long long> a(n);
    for (auto &e : a) scanf("%lld", &e);

    std::vector<std::vector<int>> g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < q; ++i) {
        int query_type;
        scanf("%d", &query_type);

        if (query_type == 0) {
            int p, l, r, x;
            scanf("%d %d %d %d", &p, &l, &r, &x);

            auto dfs = [&](auto dfs, int u, int p, int d) -> void {
                if (d >= r) return;
                if (d >= l) {
                    a[u] += x;
                }
                for (int v : g[u]) if (v != p) {
                    dfs(dfs, v, u, d + 1);
                }
            };
            dfs(dfs, p, -1, 0);
        } else {
            int p;
            scanf("%d", &p);
            printf("%lld\n", a[p]);
        }
    }

    return 0;
}
