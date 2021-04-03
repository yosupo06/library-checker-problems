#ifndef MIN_COST_B_FLOW_GEN_CYCLE_PATH_GENERATOR_H
#define MIN_COST_B_FLOW_GEN_CYCLE_PATH_GENERATOR_H

#include <numeric>
#include <vector>

#include "common.h"

namespace cycle_path_generator {

struct Generator {
    virtual ~Generator() = default;

    virtual Flow gen_flow_for_path(const Flow lower, const Flow upper) = 0;
    virtual Flow gen_flow_for_cycle(const Flow lower, const Flow upper) = 0;
    virtual Flow gen_lower_for_flow(const Flow lower, const Flow flow) = 0;
    virtual Flow gen_upper_for_flow(const Flow flow, const Flow upper) = 0;
    virtual Cost gen_cost() = 0;
    virtual bool gen_is_cycle() = 0;
    virtual size_t gen_cycle_length(const size_t max_length) = 0;
    virtual size_t gen_path_length(const size_t max_length) = 0;
    virtual void shuffle(std::vector<size_t> &vs) = 0;

    Graph generate(const size_t n, const size_t m) {
        std::vector<size_t> vs(n);
        std::iota(vs.begin(), vs.end(), (size_t) 0);

        Graph graph(n);
        while (graph.num_edges() < m) {
            shuffle(vs);
            if (gen_is_cycle()) {
                const auto cycle_len = gen_cycle_length(std::min(m - graph.num_edges(), n));
                const Flow flow  = gen_flow_for_cycle(0, U_MAX);
                rep(i, cycle_len) {
                    const Flow lower = gen_lower_for_flow(-U_MAX, flow);
                    const Flow upper = gen_upper_for_flow(flow, +U_MAX);
                    const Cost cost = gen_cost();
                    const auto s = vs[i];
                    const auto t = vs[(i + 1) % cycle_len];
                    graph.add_edge(s, t, lower, upper, cost);
                }
            } else {
                const auto path_len = gen_path_length(std::min(m - graph.num_edges(), n - 1));
                const auto source = vs[0];
                const auto target = vs[path_len];
                const auto b_cap = std::min({U_MAX, U_MAX - graph.bs[source], U_MAX + graph.bs[target]});
                if (b_cap <= 0) continue;
                const Flow flow = gen_flow_for_path(0, b_cap);
                graph.bs[source] += flow;
                graph.bs[target] -= flow;
                rep(i, path_len) {
                    const Flow lower = gen_lower_for_flow(-U_MAX, flow);
                    const Flow upper = gen_upper_for_flow(flow, +U_MAX);
                    const Cost cost = gen_cost();
                    const auto s = vs[i];
                    const auto t = vs[i + 1];
                    graph.add_edge(s, t, lower, upper, cost);
                }
            }
        }
        return graph;
    }
};

} // namespace cycle_path_generator

#endif // MIN_COST_B_FLOW_GEN_CYCLE_PATH_GENERATOR_H
