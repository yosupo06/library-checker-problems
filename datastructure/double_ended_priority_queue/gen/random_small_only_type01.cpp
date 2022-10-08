#include <iostream>

#include "random.h"
#include "../include/test_case.hpp"

int main(int, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long seed = atoll(argv[1]);
    Random gen(seed);

    GeneratorParams params{
        /* n: */ gen.uniform<int>(N_MIN, 1000),
        /* q: */ gen.uniform<int>(Q_MIN, 1000),
        /* add (%): */ 50,
        /* min (%): */ 50,
        /* max (%): */ 0,
        /* min_val: */ V_MIN,
        /* min_val: */ V_MAX
    };
    TestCase tc = random_case(gen, params);
    tc.writeln(std::cout);
    return 0;
}