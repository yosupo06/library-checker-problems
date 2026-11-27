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
    long long solve() {
        long long value = 0;
        std::vector<int> parent(n);
        while (true) {
            std::fill(parent.begin(), parent.end(), -1);
            parent[s] = -2;
            std::vector<int> queue = {s};
            for (int at = 0; at < int(queue.size()) && parent[t] == -1; ++at) {
                for (int id : adj[queue[at]]) {
                    const auto& e = edges[id];
                    if (e.cap > 0 && parent[e.to] == -1) {
                        parent[e.to] = id;
                        queue.push_back(e.to);
                    }
                }
            }
            if (parent[t] == -1) break;
            long long amount = 1LL << 60;
            for (int v = t; v != s; v = edges[parent[v]].from) {
                amount = std::min(amount, edges[parent[v]].cap);
            }
            for (int v = t; v != s; v = edges[parent[v]].from) send(parent[v], amount);
            value += amount;
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
