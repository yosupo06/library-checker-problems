#include <iostream>

#include "../params.h"
#include "random.h"

#include "../include/tree_height.hpp"
#include "../include/test_case.hpp"
#include "../include/gen_tree.hpp"

int main(int, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long seed = atoll(argv[1]);
    Random gen(seed);

    const int n = N_MAX, q = Q_MAX;

    TestCase tc(n, q);
    tc.set_random_init_values(gen);
    auto edges = random_edges(n, gen);
    tc.add_edges(edges);
    tc.add_random_queries(gen, /* sum_query_ratio = */ 0.1, tree_height(n, edges));

    std::cout << tc << std::endl;
    return 0;
}