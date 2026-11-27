#include <algorithm>
#include <cassert>
#include <cstdio>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

struct Residual {
    struct Edge { int from, to; long long cap; };
    int n, s, t;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
    explicit Residual(int size, int source, int sink) : n(size), s(source), t(sink), adj(n) {}
    void add(int u, int v, long long c) {
        adj[u].push_back(int(edges.size())); edges.push_back({u,v,c});
        adj[v].push_back(int(edges.size())); edges.push_back({v,u,0});
    }
    void send(int id, long long amount) {
        edges[id].cap -= amount;
        edges[id ^ 1].cap += amount;
    }
    std::vector<bool> cut() const {
        std::vector<bool> seen(n); std::vector<int> queue = {s}; seen[s] = true;
        for (int at = 0; at < int(queue.size()); ++at) for (int id : adj[queue[at]]) {
            const auto& e = edges[id];
            if (e.cap > 0 && !seen[e.to]) { seen[e.to] = true; queue.push_back(e.to); }
        }
        return seen;
    }
    void output(long long value) const {
        printf("%lld\n", value);
        for (int i = 0; i < int(edges.size()) / 2; ++i) printf("%s%lld", i ? " " : "", edges[2*i+1].cap);
        putchar('\n');
        for (bool side : cut()) putchar(side ? '0' : '1');
        putchar('\n');
    }
};

// Ahuja-Orlin excess scaling: minimum-label vertex with e(v)>Delta/2,
// push bounded by Delta-e(w). Binary heap selection adds logarithmic overhead.
// Algorithmic reference (no source copied): Orlin-Gong, arXiv:1910.04848,
// section 4 (k=2), and the original Ahuja-Orlin excess-scaling rule.
struct ExcessScaling : Residual {
    using Residual::Residual;
    long long solve() {
        std::vector<long long> excess(n);
        std::vector<int> height(n, n + 1), current(n);
        for (int id : adj[s]) {
            if (edges[id].to == s) continue;
            long long sent = edges[id].cap;
            send(id, sent);
            excess[edges[id].to] += sent;
            excess[s] -= sent;
        }
        std::vector<int> queue = {t};
        height[t] = 0;
        for (int at = 0; at < int(queue.size()); ++at) {
            for (int id : adj[queue[at]]) {
                int v = edges[id].to;
                if (v != s && height[v] == n + 1 && edges[id ^ 1].cap > 0) {
                    height[v] = height[queue[at]] + 1;
                    queue.push_back(v);
                }
            }
        }
        height[s] = n;
        long long delta = 1;
        for (int v = 0; v < n; ++v) {
            if (v != s && v != t) {
                while (delta < excess[v]) delta *= 2;
            }
        }
        for (; delta; delta /= 2) {
            using Item = std::pair<int, int>;
            std::priority_queue<Item, std::vector<Item>, std::greater<Item>> active;
            auto enqueue = [&](int v) {
                if (v != s && v != t && excess[v] > delta / 2) {
                    active.emplace(height[v], v);
                }
            };
            for (int v = 0; v < n; ++v) enqueue(v);
            while (!active.empty()) {
                auto [label, u] = active.top();
                active.pop();
                if (label != height[u] || excess[u] <= delta / 2) continue;
                while (current[u] < int(adj[u].size())) {
                    int id = adj[u][current[u]];
                    if (edges[id].cap > 0 && height[u] == height[edges[id].to] + 1) break;
                    ++current[u];
                }
                if (current[u] == int(adj[u].size())) {
                    int h = 2 * n;
                    for (int id : adj[u]) {
                        if (edges[id].cap > 0 && edges[id].to != u) {
                            h = std::min(h, height[edges[id].to] + 1);
                        }
                    }
                    assert(h < 2 * n);
                    height[u] = h;
                    current[u] = 0;
                    enqueue(u);
                    continue;
                }
                int id = adj[u][current[u]], v = edges[id].to;
                long long amount = std::min(excess[u], edges[id].cap);
                if (v != s && v != t) amount = std::min(amount, delta - excess[v]);
                assert(amount > 0);
                send(id, amount);
                excess[u] -= amount;
                excess[v] += amount;
                enqueue(v);
                enqueue(u);
            }
        }
        for (int v = 0; v < n; ++v) assert(v == s || v == t || excess[v] == 0);
        return excess[t];
    }
};
int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    ExcessScaling flow(n, s, t);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        scanf("%d %d %lld", &u, &v, &c);
        flow.add(u, v, c);
    }
    flow.output(flow.solve());
}
