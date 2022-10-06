#include <iostream>

#include "random.h"
#include "../include/test_case.hpp"

int main(int, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long seed = atoll(argv[1]);
    Random gen(seed);

    GeneratorParams params{
        /* n: */ N_MAX,
        /* q: */ Q_MAX,
        /* add (%): */ 20,
        /* min (%): */ 40,
        /* max (%): */ 40,
        /* min_val: */ V_MIN,
        /* min_val: */ V_MAX
    };
    TestCase tc = random_case(gen, params);
    tc.writeln(std::cout);
    return 0;
}