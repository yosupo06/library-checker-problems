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
        
        long long len = SbtOperators::depth({ a, b });
        long long k = gen.uniform<long long>(K_MIN_ANCESTOR, std::min<long long>(len, K_MAX_ANCESTOR));
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    return 0;
}
