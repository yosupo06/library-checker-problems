#include <iostream>
#include <cinttypes>
#include "random.h"
#include "../params.h"
#include "../lib/prime.hpp"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    PrimeGenerator pgen;
    
    int Q = MAX_Q;
    printf("%d\n", Q);
    for(int i = 0; i < Q; i++) {
        printf("%" PRIu64 "\n", pgen.gen(MAX_N, gen));
    }
}
