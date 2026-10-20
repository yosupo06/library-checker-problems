#include <algorithm>
#include <cstdio>
#include <vector>

struct Flow {
    struct Edge { int from, to; long long cap; };
    int n, s, t;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;

    Flow(int size, int source, int sink) : n(size), s(source), t(sink), adj(n) {}

    void add_edge(int u, int v, long long c) {
        adj[u].push_back(int(edges.size()));
        edges.push_back({u, v, c});
        adj[v].push_back(int(edges.size()));
        edges.push_back({v, u, 0});
    }

    void send(int id, long long amount) {
        edges[id].cap -= amount;
        edges[id ^ 1].cap += amount;
    }

    std::vector<bool> source_side() const {
        std::vector<bool> seen(n);
        std::vector<int> queue = {s};
        seen[s] = true;
        for (int at = 0; at < int(queue.size()); ++at) {
            for (int id : adj[queue[at]]) {
                const auto& e = edges[id];
                if (e.cap > 0 && !seen[e.to]) {
                    seen[e.to] = true;
                    queue.push_back(e.to);
                }
            }
        }
        return seen;
    }
    std::vector<bool> visited;

    long long dfs(int u, long long limit, long long threshold) {
        if (u == t) return limit;
        visited[u] = true;
        for (int id : adj[u]) {
            const auto& e = edges[id];
            if (e.cap < threshold || visited[e.to]) continue;
            long long sent = dfs(e.to, std::min(limit, e.cap), threshold);
            if (sent == 0) continue;
            send(id, sent);
            return sent;
        }
        return 0;
    }

    long long solve() {
        visited.resize(n);
        long long value = 0;
        for (long long threshold = 1; threshold > 0; threshold /= 2) {
            while (true) {
                std::fill(visited.begin(), visited.end(), false);
                long long sent = dfs(s, 1LL << 60, threshold);
                if (sent == 0) break;
                value += sent;
            }
        }
        return value;
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    Flow flow(n, s, t);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        scanf("%d %d %lld", &u, &v, &c);
        flow.add_edge(u, v, c);
    }
    printf("%lld\n", flow.solve());
    for (int i = 0; i < m; ++i) {
        printf("%s%lld", i ? " " : "", flow.edges[2 * i + 1].cap);
    }
    putchar('\n');
    for (bool side : flow.source_side()) putchar(side ? '0' : '1');
    putchar('\n');
}
