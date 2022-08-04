#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;

    std::vector<std::vector<int>> g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < q; ++i) {
        int query_type;
        std::cin >> query_type;

        if (query_type == 0) {
            int p, x;
            std::cin >> p >> x;
            a[p] += x;
        } else {
            int p, l, r;
            std::cin >> p >> l >> r;

            auto dfs = [&](auto dfs, int u, int p, int d) -> long long {
                if (d >= r) return 0;
                long long res = d >= l ? a[u] : 0;
                for (int v : g[u]) if (v != p) {
                    res += dfs(dfs, v, u, d + 1);
                }
                return res;
            };
            std::cout << dfs(dfs, p, -1, 0) << '\n';
        }
    }

    return 0;
}
