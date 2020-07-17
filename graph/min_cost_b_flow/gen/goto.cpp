#include <algorithm>

#include "common.h"
#include "extended_random.h"

// Based on Gordberg's grid-on-tours generator.
// Described in the appendix of
// Goldberg, Andrew V., and Michael Kharitonov. "On Implementing Scaling Push-Relabel Algorithms for the Minimum-Cost Flow Problem." Network Flows and Matching. 1991.

using namespace std;

struct Params {
    size_t n;
    size_t m;
    size_t x_size;
    size_t y_size;
    size_t x_degree;
    size_t y_degree;
    Flow max_cap;
    Flow max_cost;
};

size_t num_required_edges(const Params &params) {
    const size_t grid_nodes = params.x_size * params.y_size;
    size_t e = 0;
    // grid edges
    e += grid_nodes * (params.x_degree + params.y_degree);
    // edges we don't use
    e -= params.y_size * (params.x_degree * (params.x_degree + 1) / 2);
    // hamiltonian path
    e += grid_nodes - 1;
    // extra node path
    if (grid_nodes < params.n) e += params.n - grid_nodes + 1;
    return e;
}

Graph generate_goto(Random &rng, const Params &params) {
    Graph g{params.n};
    auto id = [&](const size_t x, const size_t y) -> auto { return y * params.x_size + x; };
    const auto S = id(0, 0);
    const auto T = id(params.x_size-1, params.y_size-1);

    const double alpha = pow(params.max_cap, 1.0 / (std::max(params.x_degree, params.y_degree) + 2));
    Flow demand = 0;
    rep(x, params.x_size) rep(y, params.y_size) {
        REP(dx, 1, params.x_degree+1) {
            const Flow cap_limit = (Flow) ceil((double)params.max_cap / pow(alpha, dx - 1));
            const Flow cap = rng.uniform((Flow) 1, cap_limit);
            const Cost cost = rng.uniform((Cost) 0, params.max_cost);
            if (x + dx >= params.x_size) {
                demand += cap;
            } else {
                g.add_edge(id(x, y), id((x + dx) % params.x_size, y), 0, cap, cost);
            }
        }
        REP(dy, 1, params.y_degree+1) {
            const Flow cap = rng.uniform((Flow) 1, params.max_cap);
            const Cost cost = rng.uniform(0, 8);
            g.add_edge(id(x, y), id(x, (y + dy) % params.y_size), 0, cap, cost);
        }
    }

    const Cost big_cost = std::max((Cost)1, (Cost)(params.max_cost / params.y_size));
    rep(x, params.x_size) rep(y, params.y_size) {
        if (id(x, y) == T) continue;
        const auto xx = (y + 1 == params.y_size ? x+1 : x);
        const auto yy = (y + 1 == params.y_size ? 0 : y+1);
        g.add_edge(id(x, y), id(xx, yy), 0, demand, big_cost);
    }

    g.bs[S] = +demand;
    g.bs[T] = -demand;

    Flow flow_max = demand;
    for (auto &e : g.es) flow_max = std::max(flow_max, e.upper);
    const double r = ((double) flow_max) / params.max_cap;
    for (auto &b : g.bs) b = std::min((Flow) (b * r), params.max_cap);
    for (auto &b : g.bs) b = std::max(b, -params.max_cap);
    for (auto &e : g.es) e.upper = std::min((Flow) (e.upper * r), params.max_cap);

    if (T+1 < params.n) {
        const auto extra_start = T+1;
        const auto small_cap = (Flow) ceil(sqrt(params.max_cap));
        for (auto prev = S, v = extra_start; v < params.n; prev = v++) {
            g.add_edge(prev, v, 0, small_cap, params.max_cost / 2);
        }
        g.add_edge(params.n-1, T, 0, small_cap, params.max_cost / 2);
    }
    while (g.num_edges() < params.m) {
        size_t a = rng.uniform(S+1, T-1);
        size_t b = 0;
        if (T+1 <= params.n-1) {
            rng.uniform(T+1, params.n-1);
            if (rng.uniform_bool()) std::swap(a, b);
        } else {
            do {
                b = rng.uniform(S+1, T-1);
            } while (a == b);
        }
        const Flow cap_limit = (Flow) ceil((double)params.max_cap / pow(alpha, params.x_degree - 1));
        const auto cap = rng.uniform((Flow) 1, cap_limit);
        const auto cost = rng.uniform(0, 8);
        g.add_edge(a, b, 0, cap, cost);
    }
    return g;
}

size_t qbrti(const size_t a) {
    size_t t = 1;
    while (t * t * t <= a) ++t;
    return --t;
}
Params get_params(const size_t n, const size_t m) {
    size_t y = qbrti(n);
    size_t x = y * y;
    while ((y+1) * x <= n) ++y;
    while (y * (x+1) <= n) ++x;
    Params params{};
    params.n = n;
    params.m = m;
    params.x_size = x;
    params.y_size = y;
    params.max_cap = U_MAX;
    params.max_cost = C_MAX;

    params.y_degree = 1;
    params.x_degree = 1;
    while (num_required_edges(params) < params.m) {
        ++params.y_degree;
        params.x_degree = params.y_degree * params.y_degree;
    }
    --params.y_degree;
    params.x_degree = params.y_degree * params.y_degree;
    while (num_required_edges(params) < params.m) ++params.x_degree;
    --params.x_degree;
    return params;
}

int main(const int, const char* argv[]) {
    using namespace std;

    long long seed = atoll(argv[1]);
    auto rng = Rng(seed);

    const Params params = get_params(N_MAX, M_MAX);
    auto graph = generate_goto(rng, params);
    graph.shuffle(rng);
    graph.output();
    return 0;
}
