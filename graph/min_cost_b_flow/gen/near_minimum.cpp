#include <algorithm>

#include "common.h"
#include "extended_random.h"
#include "cycle_path_generator.h"

struct Generator : public cycle_path_generator::Generator {
    Rng &rng;

    Generator(Rng &rng) : rng(rng) { }

    Flow gen_flow_for_path(const Flow lower, const Flow upper) override {
        return rng.skewed(lower, upper, upper);
    }
    Flow gen_flow_for_cycle(const Flow lower, const Flow upper) override {
        return rng.skewed(lower, upper, upper);
    }
    Flow gen_lower_for_flow(const Flow lower, const Flow flow) override {
        return rng.skewed(lower, flow, flow);
    }
    Flow gen_upper_for_flow(const Flow flow, const Flow upper) override {
        return rng.skewed(flow, flow, upper);
    }
    Cost gen_cost() override {
        return rng.template skewed<Flow>(-C_MAX, -C_MAX, 0);
    }
    bool gen_is_cycle() override {
        return rng.uniform_bool();
    }
    size_t gen_cycle_length(const size_t max_length) override {
        return rng.template skewed<size_t>(1, 1, max_length);
    }
    size_t gen_path_length(const size_t max_length) override {
        return rng.template skewed<size_t>(1, 1, max_length);
    }
    void shuffle(std::vector<size_t> &vs) override {
        rng.shuffle(vs.begin(), vs.end());
    }
};

int main(const int, const char* argv[]) {
    using namespace std;

    long long seed = atoll(argv[1]);
    auto rng = Rng(seed);
    Generator gen{rng};

    auto graph = gen.generate(N_MAX, M_MAX);
    graph.shuffle(rng);
    graph.flip_edges_randomly(rng);
    graph.output();
    return 0;
}
