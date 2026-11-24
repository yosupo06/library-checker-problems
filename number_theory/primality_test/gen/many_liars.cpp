#include <iostream>
#include <cinttypes>
#include "random.h"
#include "../params.h"
#include "../lib/prime.hpp"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    ll seed = atoll(argv[1]);
    auto gen = Random(seed);
    PrimeGenerator pgen;
    
    int Q = MAX_Q;
    printf("%d\n", Q);
    for(int i = 0; i < Q; i++) {
        // these composites are strong pseudoprimes to almost 25% of bases
        u64 p, q;
        do {
            p = pgen.gen(sqrt(MAX_N / 2), gen);
            q = 2 * p - 1;
        } while (!is_prime(q));
        printf("%" PRIu64 "\n", p * q);
    }
}
