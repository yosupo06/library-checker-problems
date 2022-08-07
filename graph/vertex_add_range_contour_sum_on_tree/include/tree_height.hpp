#ifndef INCLUDE_TREE_HEIGHT
#define INCLUDE_TREE_HEIGHT

#include <algorithm>
#include <deque>
#include <vector>

std::vector<int> tree_height(const int n, const std::vector<std::pair<int, int>> &edges) {
    std::vector<std::vector<int>> g(n);
    for (auto e : edges) {
        int u, v;
        std::tie(u, v) = e;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto dist = [&](int s) {
        std::vector<int> d(n, -1);
        d[s] = 0;
        std::deque<int> dq { s };
        while (dq.size()) {
            int u = dq.front();
            dq.pop_front();
            for (int v : g[u]) if (d[v] < 0) {
                d[v] = d[u] + 1;
                dq.push_back(v);
            }
        }
        return d;
    };

    auto d0 = dist(0);
    int x = std::max_element(d0.begin(), d0.end()) - d0.begin();
    auto dx = dist(x);
    int y = std::max_element(dx.begin(), dx.end()) - dx.begin();
    auto dy = dist(y);

    std::vector<int> res(n);
    for (int i = 0; i < n; ++i) res[i] = std::max(dx[i], dy[i]);
    return res;
}

#endif // INCLUDE_TREE_HEIGHT