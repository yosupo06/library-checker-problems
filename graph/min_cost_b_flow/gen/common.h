#ifndef MIN_COST_B_FLOW_GEN_COMMON_H
#define MIN_COST_B_FLOW_GEN_COMMON_H

#include <cassert>
#include <cstdio>
#include <tuple>
#include <vector>

#include "../params.h"

#define rep(i, n) for (size_t i = 0; i < (size_t)(n); ++i)
#define loop(n) rep(i##__COUNTER__, n)

using Flow = long long int;
using Cost = long long int;

struct Edge {
    size_t s, t;
    Flow lower, upper;
    Cost cost;
    Edge() = default;
    Edge(Edge &&) = default;
    Edge(const Edge &) = default;
    Edge(const size_t s, const size_t t, const Flow lower, const Flow upper, const Cost cost)
        : s(s), t(t), lower(lower), upper(upper), cost(cost) { }
    Edge &operator=(const Edge &) = default;
    Edge &operator=(Edge &&) = default;
};

struct Graph {
    std::vector<Flow> bs;
    std::vector<Edge> es;

    Graph(const size_t n) : bs(n, 0) {}

    template<class ...Args>
    void add_edge(Args &&...args) {
        es.emplace_back(std::forward<Args>(args)...);
    }

    size_t num_vertices() const {
        return bs.size();
    }

    size_t num_edges() const {
        return es.size();
    }

    bool satisfies_constraints() {
        const auto n = bs.size();
        const auto m = es.size();
        if (n > N_MAX) return false;
        if (m > M_MAX) return false;
        for (const auto &b : bs) {
            if (b < -U_MAX || U_MAX < b) return false;
        }
        for (const auto &e : es) {
            if (e.s >= n) return false;
            if (e.t >= n) return false;
            if (e.lower < -U_MAX || U_MAX < e.lower) return false;
            if (e.upper < -U_MAX || U_MAX < e.upper) return false;
            if (e.lower > e.upper) return false;
            if (e.cost < -C_MAX || C_MAX < e.cost) return false;
        }
        return true;
    }

    template<class Gen>
    void shuffle(Gen &gen) {
        const auto old_to_new = gen.template perm<size_t>(num_vertices());
        gen.shuffle(std::begin(es), std::end(es));
        const auto bs_bck = bs;
        rep(v, num_vertices()) bs[old_to_new[v]] = bs_bck[v];
        for (auto &e : es) {
            e.s = old_to_new[e.s];
            e.t = old_to_new[e.t];
        }
    }

    template<class Gen>
    void flip_edges_randomly(Gen &gen) {
        for (auto &e : es) {
            if (gen.uniform_bool()) {
                std::tie(e.s, e.t) = std::make_pair(e.t, e.s);
                std::tie(e.lower, e.upper) = std::make_pair(-e.upper, -e.lower);
                e.cost = -e.cost;
            }
        }
    }

    void output() {
        assert(satisfies_constraints());
        printf("%llu %llu\n", (unsigned long long int) bs.size(), (unsigned long long int) es.size());
        for (const auto &b : bs) {
            printf("%lld\n", b);
        }
        for (const auto &e : es) {
            printf("%llu %llu %lld %lld %lld\n", (unsigned long long int) e.s, (unsigned long long int) e.t, e.lower, e.upper, e.cost);
        }
    }
};


#endif // MIN_COST_B_FLOW_GEN_COMMON_H
