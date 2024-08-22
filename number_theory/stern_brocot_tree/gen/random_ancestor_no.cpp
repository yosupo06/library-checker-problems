#include "random.h"
#include "../params.h"
#include "../lib/lib.hpp"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

#include <algorithm>

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long T1 = T_MAX / 3;
    long long T2 = T_MAX - T1;
    
    printf("%lld\n", T1 + T2);

    for(long long i=0; i<T1; i++){
        auto [a, b] = RandomCoprime(gen, TARGET_FRAC_MAX);
        long long len = SbtOperators::depth({ a, b });
        if(K_MAX_ANCESTOR <= len){ i--; continue; }

        long long k = gen.uniform<long long>(len + 1, K_MAX_ANCESTOR);
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    for(long long i=0; i<T2; i++){
        auto [a, b] = RandomCoprime(gen, TARGET_FRAC_MAX);
        long long len = SbtOperators::depth({ a, b });
        if(K_MAX_ANCESTOR <= len){ i--; continue; }

        long long k = gen.uniform<long long>(len + 1, std::min<long long>(K_MAX_ANCESTOR, len + 100));
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    return 0;
}
