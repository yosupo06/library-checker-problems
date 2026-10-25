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
        std::vector<int> distance(n, n), gap(n + 1), current(n), parent(n, -1);
        std::vector<int> queue = {t};
        distance[t] = 0;
        for (int at = 0; at < int(queue.size()); ++at) {
            for (int id : adj[queue[at]]) {
                int v = edges[id].to;
                if (edges[id ^ 1].cap > 0 && distance[v] == n) {
                    distance[v] = distance[queue[at]] + 1;
                    queue.push_back(v);
                }
            }
        }
        for (int d : distance) ++gap[d];
        long long value = 0;
        int u = s;
        while (distance[s] < n) {
            if (u == t) {
                long long sent = 1LL << 60;
                for (int v = t; v != s; v = edges[parent[v]].from) {
                    sent = std::min(sent, edges[parent[v]].cap);
                }
                for (int v = t; v != s; v = edges[parent[v]].from) send(parent[v], sent);
                value += sent;
                u = s;
                continue;
            }
            bool advanced = false;
            for (int& i = current[u]; i < int(adj[u].size()); ++i) {
                int id = adj[u][i];
                if (edges[id].cap > 0 && distance[u] == distance[edges[id].to] + 1) {
                    parent[edges[id].to] = id;
                    u = edges[id].to;
                    advanced = true;
                    break;
                }
            }
            if (advanced) continue;
            int old = distance[u], next = n - 1;
            for (int id : adj[u]) {
                if (edges[id].cap > 0) next = std::min(next, distance[edges[id].to]);
            }
            if (--gap[old] == 0) break;
            distance[u] = next + 1;
            ++gap[distance[u]];
            current[u] = 0;
            if (u != s) u = edges[parent[u]].from;
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
