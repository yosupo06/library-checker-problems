#include "random.h"
#include "../params.h"
#include "../lib/lib.hpp"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int T = T_MAX;
    
    printf("%d\n", T);

    for(int i=0; i<T; i++){
        long long a = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long b = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long g_ab = Gcd(a, b);
        a /= g_ab; b /= g_ab;
        
        long long c = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long d = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long g_cd = Gcd(c, d);
        c /= g_cd; d /= g_cd;
        
        printf("LCA %lld %lld %lld %lld\n", a, b, c, d);
    }

    return 0;
}
