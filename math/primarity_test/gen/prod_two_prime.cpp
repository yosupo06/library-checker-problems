#include <iostream>
#include <cinttypes>
#include "random.h"
#include "../params.h"
#include "../lib/prime.hpp"

using namespace std;
using ll = long long;

const u64 PRIME_UPPER = 1'000'000'000;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    PrimeGenerator pgen;
    
    int Q = 100000;
    printf("%d\n", Q);
    for(int i = 0; i < Q; i++) {
        u64 a = pgen.gen(PRIME_UPPER, gen);
        u64 b = pgen.gen(PRIME_UPPER, gen);
        printf("%" PRIu64 "\n", a * b);
    }
}
