// Deliberately ignore reverse residual arcs.
#include <algorithm>
#include <cstdio>
#include <vector>

struct Dinic {
    struct Edge { int to; long long cap; };
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> level, current;

    explicit Dinic(int n_) : n(n_), adj(n), level(n), current(n) {}

    void add_edge(int u, int v, long long c) {
        adj[u].push_back(int(edges.size()));
        edges.push_back({v, c});
        adj[v].push_back(int(edges.size()));
        edges.push_back({u, 0});
    }

    bool bfs(int s, int t, long long threshold) {
        std::fill(level.begin(), level.end(), -1);
        std::vector<int> queue = {s};
        level[s] = 0;
        for (int i = 0; i < int(queue.size()); ++i) {
            int u = queue[i];
            for (int id : adj[u]) {
                const auto& e = edges[id];
                if (!(id & 1) && e.cap >= threshold && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    queue.push_back(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    long long dfs(int u, int t, long long limit, long long threshold) {
        if (u == t) return limit;
        int& i = current[u];
        for (; i < int(adj[u].size()); ++i) {
            const int id = adj[u][i];
            auto& e = edges[id];
            if ((id & 1) || e.cap < threshold || level[e.to] != level[u] + 1) continue;
            const long long sent = dfs(e.to, t, std::min(limit, e.cap), threshold);
            if (sent == 0) continue;
            e.cap -= sent;
            edges[id ^ 1].cap += sent;
            return sent;
        }
        return 0;
    }

    long long solve(int s, int t) {
        long long value = 0;
        long long threshold = 1LL << 29;
        for (; threshold > 0; threshold /= 2) {
            while (bfs(s, t, threshold)) {
                std::fill(current.begin(), current.end(), 0);
                while (long long sent = dfs(s, t, 1LL << 60, threshold)) {
                    value += sent;
                }
            }
        }
        return value;
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    Dinic flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        scanf("%d %d %lld", &u, &v, &c);
        flow.add_edge(u, v, c);
    }
    printf("%lld\n", flow.solve(s, t));
    for (int i = 0; i < m; ++i) {
        printf("%s%lld", i ? " " : "", flow.edges[2 * i + 1].cap);
    }
    printf("\n");
    for (int v = 0; v < n; ++v) putchar(flow.level[v] < 0 ? '1' : '0');
    putchar('\n');
}
