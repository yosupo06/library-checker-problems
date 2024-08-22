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
            int p, x;
            scanf("%d %d", &p, &x);
            a[p] += x;
        } else {
            int p, l, r;
            scanf("%d %d %d", &p, &l, &r);

            auto dfs = [&](auto dfs, int u, int p, int d) -> long long {
                if (d >= r) return 0;
                long long res = d >= l ? a[u] : 0;
                for (int v : g[u]) if (v != p) {
                    res += dfs(dfs, v, u, d + 1);
                }
                return res;
            };
            long long ans = dfs(dfs, p, -1, 0);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
