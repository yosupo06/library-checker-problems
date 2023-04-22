#include "random.h"
#include "../params.h"
#include "../lib/lib.hpp"

#include <algorithm>

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int T1 = T_MAX / 3;
    int T2 = T_MAX - T1;
    
    printf("%d\n", T1 + T2);

    for(int i=0; i<T1; i++){
        long long a = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long b = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long g_ab = Gcd(a, b);
        a /= g_ab; b /= g_ab;

        auto path = SbtOperators::encode({ a, b });
        long long len = 0;
        for(auto cn : path) len += cn.second;
        if(K_MAX_ANCESTOR <= len){ i--; continue; }

        long long k = gen.uniform<long long>(len + 1, K_MAX_ANCESTOR);
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    for(int i=0; i<T2; i++){
        long long a = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long b = gen.uniform<long long>(1, TARGET_FRAC_MAX);
        long long g_ab = Gcd(a, b);
        a /= g_ab; b /= g_ab;
        
        auto path = SbtOperators::encode({ a, b });
        long long len = 0;
        for(auto cn : path) len += cn.second;
        if(K_MAX_ANCESTOR <= len){ i--; continue; }

        long long k = gen.uniform<long long>(len + 1, std::min<long long>(K_MAX_ANCESTOR, len + 100));
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    return 0;
}
