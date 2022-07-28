#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>
#include <limits>

enum Objective {
    MINIMIZE = 1,
    MAXIMIZE = -1,
};
enum class Status {
    OPTIMAL,
    INFEASIBLE,
};

template <class Flow, class Cost, Objective objective = Objective::MINIMIZE>
class MinCostFlow {
    using V_id = uint32_t;
    using E_id = uint32_t;

    class Edge {
        friend class MinCostFlow;

        V_id src, dst;
        Flow flow, cap;
        Cost cost;
        E_id rev;

        public:
        Edge() = default;

        Edge(const V_id src, const V_id dst, const Flow cap, const Cost cost,
             const E_id rev)
            : src(src), dst(dst), flow(0), cap(cap), cost(cost), rev(rev) {}

        [[nodiscard]] Flow residual_cap() const { return cap - flow; }
    };

    public:
    class EdgePtr {
        friend class MinCostFlow;

        const MinCostFlow *instance;
        V_id v;
        E_id e;

        EdgePtr(const MinCostFlow * const instance, const V_id v, const E_id e)
            : instance(instance), v(v), e(e) {}

        [[nodiscard]] const Edge &edge() const { return instance->g[v][e]; }

        [[nodiscard]] const Edge &rev() const {
            const Edge &e = edge();
            return instance->g[e.dst][e.rev];
        }

        public:
        EdgePtr() = default;

        [[nodiscard]] V_id src() const { return v; }

        [[nodiscard]] V_id dst() const { return edge().dst; }

        [[nodiscard]] Flow flow() const { return edge().flow; }

        [[nodiscard]] Flow lower() const { return -rev().cap; }

        [[nodiscard]] Flow upper() const { return edge().cap; }

        [[nodiscard]] Cost cost() const { return edge().cost; }

        [[nodiscard]] Cost gain() const { return -edge().cost; }
    };

    private:
    V_id n;
    std::vector<std::vector<Edge>> g;
    std::vector<Flow> b;

    public:
    MinCostFlow() : n(0) {}

    V_id add_vertex() {
        ++n;
        g.resize(n);
        b.resize(n);
        return n-1;
    }

    std::vector<V_id> add_vertices(const size_t size) {
        std::vector<V_id> ret(size);
        std::iota(std::begin(ret), std::end(ret), n);
        n += size;
        g.resize(n);
        b.resize(n);
        return ret;
    }

    EdgePtr add_edge(const V_id src, const V_id dst, const Flow lower,
                     const Flow upper, const Cost cost) {
        const E_id e = g[src].size(), re = src == dst ? e + 1 : g[dst].size();
        assert(lower <= upper);
        g[src].emplace_back(Edge{src, dst, upper, cost * objective, re});
        g[dst].emplace_back(Edge{dst, src, -lower, -cost * objective, e});
        return EdgePtr{this, src, e};
    }

    void add_supply(const V_id v, const Flow amount) { b[v] += amount; }

    void add_demand(const V_id v, const Flow amount) { b[v] -= amount; }

    private:
    // Variables used in calculation
    const Cost unreachable = std::numeric_limits<Cost>::max();
    Cost farthest;
    std::vector<Cost> potential;
    std::vector<Cost> dist;
    std::vector<Edge *> parent; // out-forrest.
    std::priority_queue<std::pair<Cost, int>, std::vector<std::pair<Cost, int>>,
        std::greater<>>
            pq; // should be empty outside of dual()
    std::vector<V_id> excess_vs, deficit_vs;

    Edge &rev(const Edge &e) { return g[e.dst][e.rev]; }

    void push(Edge &e, const Flow amount) {
        e.flow += amount;
        g[e.dst][e.rev].flow -= amount;
    }

    Cost residual_cost(const V_id src, const V_id dst, const Edge &e) {
        return e.cost + potential[src] - potential[dst];
    }

    bool dual(const Flow delta) {
        dist.assign(n, unreachable);
        parent.assign(n, nullptr);
        excess_vs.erase(std::remove_if(std::begin(excess_vs), std::end(excess_vs),
                                       [&](const V_id v) { return b[v] < delta; }),
                        std::end(excess_vs));
        deficit_vs.erase(std::remove_if(std::begin(deficit_vs),
                                        std::end(deficit_vs),
                                        [&](const V_id v) { return b[v] > -delta; }),
                         std::end(deficit_vs));
        for (const auto v : excess_vs) pq.emplace(dist[v] = 0, v);
        farthest = 0;
        std::size_t deficit_count = 0;
        while (!pq.empty()) {
            Cost d;
            std::size_t u;
            std::tie(d, u) = pq.top();
            // const auto [d, u] = pq.top();
            pq.pop();
            if (dist[u] < d) continue;
            farthest = d;
            if (b[u] <= -delta) ++deficit_count;
            if (deficit_count >= deficit_vs.size()) break;
            for (auto &e : g[u]) {
                if (e.residual_cap() < delta) continue;
                const auto v = e.dst;
                const auto new_dist = d + residual_cost(u, v, e);
                if (new_dist >= dist[v]) continue;
                pq.emplace(dist[v] = new_dist, v);
                parent[v] = &e;
            }
        }
        pq = decltype(pq)(); // pq.clear() doesn't exist.
        for (V_id v = 0; v < n; ++v) {
            potential[v] += std::min(dist[v], farthest);
        }
        return deficit_count > 0;
    }

    void primal(const Flow delta) {
        for (const auto t : deficit_vs) {
            if (dist[t] > farthest) continue;
            Flow f = -b[t];
            V_id v;
            for (v = t; parent[v] != nullptr; v = parent[v]->src) {
                f = std::min(f, parent[v]->residual_cap());
            }
            f = std::min(f, b[v]);
            f -= f % delta;
            if (f <= 0) continue;
            for (v = t; parent[v] != nullptr;) {
                auto &e = *parent[v];
                push(e, f);
                int u = parent[v]->src;
                if (e.residual_cap() <= 0) parent[v] = nullptr;
                v = u;
            }
            b[t] += f;
            b[v] -= f;
        }
    }

    void saturate_negative(const Flow delta) {
        for (auto &es : g) for (auto &e : es) {
            Flow rcap = e.residual_cap();
            rcap -= rcap % delta;
            const Cost rcost = residual_cost(e.src, e.dst, e);
            if (rcost < 0 || rcap < 0) {
                push(e, rcap);
                b[e.src] -= rcap;
                b[e.dst] += rcap;
            }
        }
        for (V_id v = 0; v < n; ++v) if (b[v] != 0) {
            (b[v] > 0 ? excess_vs : deficit_vs).emplace_back(v);
        }
    }

    public:
    std::pair<Status, Cost> solve() {
        potential.resize(n);

        saturate_negative(1);
        while (dual(1)) primal(1);

        Cost value = 0;
        for (const auto &es : g) for (const auto &e : es) {
            value += e.flow * e.cost;
        }
        value /= 2;

        if (excess_vs.empty() && deficit_vs.empty()) {
            return { Status::OPTIMAL, value / objective };
        } else {
            return { Status::INFEASIBLE, value / objective };
        }
    }

    std::vector<Cost> get_potential() {
        return potential;
    }
    template<class T>
    T get_result_value() {
        T value = 0;
        for (const auto &es : g) for (const auto &e : es) {
            value += (T)(e.flow) * (T)(e.cost);
        }
        value /= (T)2;
        return value;
    }
};

#if __INCLUDE_LEVEL__ == 0

#include <cstdint>
#include <cstdio>
#define REP(i, b, n) for (int i = (int)(b); i < (int)(n); ++i)
#define rep(i, n) REP(i, 0, n)
#define loop(n) rep(i##__COUNTER__, n)

int readI() {
    int n;
    scanf("%d", &n);
    return n;
}
long long readLL() {
    long long n;
    scanf("%lld", &n);
    return n;
}

template<class T>
std::string i2s(T value) {
    if (value < 0) return "-" + i2s(-value);
    if (value == 0) return "0";
    std::string s;
    while (value) {
        s += '0' + (value % 10);
        value /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

int main(void) {
    using MCF = MinCostFlow<long long, long long>;
    const int n = readI();
    const int m = readI();
    MCF mcf;
    const auto vs = mcf.add_vertices(n);
    for (const auto &v : vs) {
        mcf.add_supply(vs[v], readLL());
    }
    std::vector<MCF::EdgePtr> edges;
    loop(m) {
        const int s = readI();
        const int t = readI();
        const int lower = readLL();
        const int upper = readLL();
        const int cost = readLL();
        edges.emplace_back(mcf.add_edge(s, t, lower, upper, cost));
    }
    const auto status = mcf.solve().first;
    if (status == Status::INFEASIBLE) {
        puts("infeasible");
    } else {
        const auto potential = mcf.get_potential();
        const auto result_value = mcf.get_result_value<__int128_t>();
        puts(i2s(result_value).c_str());
        for (const auto &v : vs) {
            puts(i2s(potential[v]).c_str());
        }
        for (const auto &e : edges) {
            puts(i2s(e.flow()).c_str());
        }
    }
}

#endif
