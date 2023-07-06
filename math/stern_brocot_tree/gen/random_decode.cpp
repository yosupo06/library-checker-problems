#include "random.h"
#include "../params.h"
#include "../lib/gen_lib.hpp"
#include "../lib/lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long T = T_MAX;
    
    printf("%lld\n", T);

    for(long long i=0; i<T; i++){
        auto [a, b] = RandomCoprime(gen, TARGET_FRAC_MAX);
        
        printf("DECODE_PATH ");
        output_path(SbtOperators::encode({ a, b }));
        printf("\n");
    }

    return 0;
}

