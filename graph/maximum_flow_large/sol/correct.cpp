#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

// Highest-label push-relabel, with global relabeling and the gap heuristic.
// Unlike a maximum-preflow-only implementation, discharge ALL active vertices,
// including those above height n, to return excess to s and obtain a flow.
struct PushRelabel {
    struct Edge { int to; long long cap; };
    int n, s, t, highest = -1;
    long long work = 0;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj, bucket;
    std::vector<int> height, current, count;
    std::vector<long long> excess;
    std::vector<bool> active;

    explicit PushRelabel(int n_) : n(n_), adj(n), bucket(2 * n + 1),
        height(n), current(n), count(2 * n + 1), excess(n), active(n) {}

    void add_edge(int u, int v, long long c) {
        adj[u].push_back(int(edges.size()));
        edges.push_back({v, c});
        adj[v].push_back(int(edges.size()));
        edges.push_back({u, 0});
    }

    void activate(int v) {
        if (v == s || v == t || excess[v] == 0 || active[v]) return;
        active[v] = true;
        bucket[height[v]].push_back(v);
        highest = std::max(highest, height[v]);
    }

    void rebuild() {
        for (auto& b : bucket) b.clear();
        std::fill(active.begin(), active.end(), false);
        std::fill(count.begin(), count.end(), 0);
        highest = -1;
        for (int v = 0; v < n; ++v) {
            ++count[height[v]];
            activate(v);
        }
    }

    void global_relabel() {
        std::fill(height.begin(), height.end(), 2 * n);
        std::fill(current.begin(), current.end(), 0);
        auto reverse_bfs = [&](int root, int base) {
            std::vector<int> queue = {root};
            height[root] = base;
            for (int i = 0; i < int(queue.size()); ++i) {
                int u = queue[i];
                for (int id : adj[u]) {
                    int v = edges[id].to;
                    if (v != s && height[v] == 2 * n && edges[id ^ 1].cap > 0) {
                        height[v] = height[u] + 1;
                        queue.push_back(v);
                    }
                }
            }
        };
        reverse_bfs(t, 0);
        // Distances to s also speed up conversion of the preflow to a flow.
        reverse_bfs(s, n);
        rebuild();
        work = 0;
    }

    void push(int u, int id) {
        auto& e = edges[id];
        const long long sent = std::min(excess[u], e.cap);
        e.cap -= sent;
        edges[id ^ 1].cap += sent;
        excess[u] -= sent;
        excess[e.to] += sent;
        activate(e.to);
    }

    long long solve(int source, int sink) {
        s = source;
        t = sink;
        for (int id : adj[s]) {
            auto& e = edges[id];
            if (e.to == s) continue;
            const long long sent = e.cap;
            e.cap = 0;
            edges[id ^ 1].cap += sent;
            excess[e.to] += sent;
            excess[s] -= sent;
        }
        global_relabel();
        while (highest >= 0) {
            if (bucket[highest].empty()) { --highest; continue; }
            const int u = bucket[highest].back();
            bucket[highest].pop_back();
            active[u] = false;
            bool rebuilt = false;
            while (excess[u] > 0) {
                if (current[u] == int(adj[u].size())) {
                    const int old = height[u];
                    int next = 2 * n;
                    for (int id : adj[u]) {
                        if (edges[id].cap > 0 && edges[id].to != u) {
                            next = std::min(next, height[edges[id].to] + 1);
                        }
                    }
                    assert(next < 2 * n);
                    height[u] = next;
                    current[u] = 0;
                    --count[old];
                    ++count[next];
                    work += int(adj[u].size());
                    if (old < n && count[old] == 0) {
                        for (int v = 0; v < n; ++v) {
                            if (v != s && v != t && old < height[v] && height[v] < n) {
                                height[v] = n + 1;
                                current[v] = 0;
                            }
                        }
                        rebuild();
                        rebuilt = true;
                        break;
                    }
                } else {
                    int id = adj[u][current[u]];
                    ++work;
                    if (edges[id].cap > 0 && height[u] == height[edges[id].to] + 1) {
                        push(u, id);
                    } else {
                        ++current[u];
                    }
                }
            }
            if (!rebuilt) activate(u);
            if (work > 4 * int(edges.size()) + n) global_relabel();
        }
        for (int v = 0; v < n; ++v) assert(v == s || v == t || excess[v] == 0);
        return excess[t];
    }

    std::vector<bool> source_side() const {
        std::vector<bool> seen(n, false);
        std::vector<int> queue = {s};
        seen[s] = true;
        for (int i = 0; i < int(queue.size()); ++i) {
            for (int id : adj[queue[i]]) {
                const auto& e = edges[id];
                if (e.cap > 0 && !seen[e.to]) {
                    seen[e.to] = true;
                    queue.push_back(e.to);
                }
            }
        }
        return seen;
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    PushRelabel flow(n);
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
    const auto side = flow.source_side();
    for (bool b : side) putchar(b ? '0' : '1');
    putchar('\n');
}
