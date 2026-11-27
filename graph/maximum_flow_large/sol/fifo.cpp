#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

// Independent FIFO implementation. First compute a maximum preflow, then
// discharge its remaining excess back to s without changing the excess at t.
struct FIFOFlow {
    struct Arc { int to, reverse; long long remaining; };
    std::vector<std::vector<Arc>> graph;
    std::vector<std::pair<int, int>> original;
    std::vector<long long> excess;
    std::vector<int> height, next;
    std::vector<bool> queued;
    std::queue<int> queue;
    int n, s, t;
    long long work = 0;

    explicit FIFOFlow(int size) : graph(size), excess(size), height(size),
        next(size), queued(size), n(size) {}

    void add(int u, int v, long long capacity) {
        const int a = int(graph[u].size());
        const int b = int(graph[v].size()) + (u == v);
        original.emplace_back(u, a);
        graph[u].push_back({v, b, capacity});
        graph[v].push_back({u, a, 0});
    }

    void enqueue(int v, bool returning) {
        if (v == s || v == t || excess[v] == 0 || queued[v]) return;
        if (!returning && height[v] >= n) return;
        queued[v] = true;
        queue.push(v);
    }

    void distances(bool returning) {
        const int root = returning ? s : t;
        const int excluded = returning ? t : s;
        const int infinity = returning ? 2 * n : n;
        std::fill(height.begin(), height.end(), infinity);
        height[root] = 0;
        std::queue<int> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            const int u = bfs.front(); bfs.pop();
            for (const auto& e : graph[u]) {
                if (e.to != excluded && height[e.to] == infinity &&
                    graph[e.to][e.reverse].remaining > 0) {
                    height[e.to] = height[u] + 1;
                    bfs.push(e.to);
                }
            }
        }
        std::fill(next.begin(), next.end(), 0);
        std::fill(queued.begin(), queued.end(), false);
        queue = std::queue<int>();
        for (int v = 0; v < n; ++v) enqueue(v, returning);
        work = 0;
    }

    void discharge(int u, bool returning) {
        while (excess[u] > 0 && (returning || height[u] < n)) {
            if (next[u] == int(graph[u].size())) {
                int h = returning ? 2 * n : n;
                for (const auto& e : graph[u]) {
                    if (e.remaining > 0 && e.to != u && (!returning || e.to != t)) {
                        h = std::min(h, height[e.to] + 1);
                    }
                }
                height[u] = h;
                next[u] = 0;
                work += int(graph[u].size());
                assert(!returning || h < 2 * n);
            } else {
                auto& e = graph[u][next[u]];
                ++work;
                if (e.remaining > 0 && height[u] == height[e.to] + 1 &&
                    (!returning || e.to != t)) {
                    long long sent = std::min(excess[u], e.remaining);
                    e.remaining -= sent;
                    graph[e.to][e.reverse].remaining += sent;
                    excess[u] -= sent;
                    excess[e.to] += sent;
                    enqueue(e.to, returning);
                } else ++next[u];
            }
        }
    }

    long long solve(int source, int sink) {
        s = source; t = sink;
        for (auto& e : graph[s]) {
            if (e.to == s) continue;
            long long sent = e.remaining;
            e.remaining = 0;
            graph[e.to][e.reverse].remaining += sent;
            excess[e.to] += sent;
            excess[s] -= sent;
        }
        for (int phase = 0; phase < 2; ++phase) {
            const bool returning = phase == 1;
            distances(returning);
            while (!queue.empty()) {
                int u = queue.front(); queue.pop(); queued[u] = false;
                discharge(u, returning);
                if (!returning && work > 4 * int(original.size()) + n) distances(false);
            }
        }
        for (int v = 0; v < n; ++v) assert(v == s || v == t || excess[v] == 0);
        return excess[t];
    }

    std::vector<bool> source_side() const {
        std::vector<bool> seen(n, false);
        std::queue<int> bfs;
        seen[s] = true;
        bfs.push(s);
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            for (const auto& e : graph[u]) {
                if (e.remaining > 0 && !seen[e.to]) {
                    seen[e.to] = true;
                    bfs.push(e.to);
                }
            }
        }
        return seen;
    }
};

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    FIFOFlow flow(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        scanf("%d %d %lld", &u, &v, &c);
        flow.add(u, v, c);
    }
    printf("%lld\n", flow.solve(s, t));
    for (int i = 0; i < m; ++i) {
        const auto [u, id] = flow.original[i];
        const auto& e = flow.graph[u][id];
        const long long f = flow.graph[e.to][e.reverse].remaining;
        printf("%s%lld", i ? " " : "", f);
    }
    printf("\n");
    for (bool b : flow.source_side()) putchar(b ? '0' : '1');
    putchar('\n');
}
