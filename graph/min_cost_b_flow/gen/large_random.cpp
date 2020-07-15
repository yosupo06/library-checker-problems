#include <algorithm>

#include "common.h"
#include "extended_random.h"
#include "basic_tree_to_graph_generator.h"

struct Generator : public basic_tree_to_graph_generator::Generator {
    Rng &rng;

    Generator(Rng &rng) : rng(rng) { }

    Cost get_cost_limit() const override { return C_MAX; }
    Flow get_flow_limit() const override { return U_MAX; }

    Tree generate_tree(const size_t n) override {
        if (rng.uniform_bool()) {
            return basic_tree_to_graph_generator::generate_tree(rng, n);
        } else {
            return basic_tree_to_graph_generator::generate_skewed_tree(rng, n);
        }
    }
    Cost gen_potential(const Cost upper) override {
        return rng.template skewed<Cost>(0, 0, upper);
    }
    Flow gen_flow_for_tree_edge(const Flow lower, const Flow upper) override {
        return rng.template skewed<Flow>(lower, 0, upper);
    }
    Flow gen_lower_for_tree_edge(const Flow lower, const Flow flow) override {
        return rng.skewed(lower, flow, flow);
    }
    Flow gen_upper_for_tree_edge(const Flow flow, const Flow upper) override {
        return rng.skewed(flow, flow, upper);
    }

    std::pair<size_t, size_t> gen_non_tree_edge(const size_t n) override {
        const size_t s = rng.skewed(n-1);
        const size_t t = rng.skewed(n-1);
        return {s, t};
    }
    Flow gen_flow_for_non_tree_edge(const Flow lower, const Flow upper) override {
        return rng.template skewed<Flow>(lower, 0, upper);
    }
    Flow gen_upper_for_lower_non_tree_edge(const Flow flow, const Flow upper) override {
        return rng.skewed(flow, upper, upper);
    }
    Cost gen_cost_for_lower_non_tree_edge(const Cost pot_diff, const Cost upper) override {
        return rng.skewed(pot_diff, pot_diff, upper);
    }
};

int main(const int, const char* argv[]) {
    using namespace std;

    long long seed = atoll(argv[1]);
    auto rng = Rng(seed);
    const size_t n = N_MAX;
    const size_t m = M_MAX;

    Generator gen{rng};
    auto graph = gen.generate(n, m);
    graph.shuffle(rng);
    graph.flip_edges_randomly(rng);
    graph.output();
    return 0;
}
