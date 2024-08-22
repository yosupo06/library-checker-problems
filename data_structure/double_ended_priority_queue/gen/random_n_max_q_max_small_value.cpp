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
        /* add (%): */ 30,
        /* min (%): */ 35,
        /* max (%): */ 35,
        /* min_val: */ -1000,
        /* min_val: */ +1000
    };
    TestCase tc = random_case(gen, params);
    tc.writeln(std::cout);
    return 0;
}