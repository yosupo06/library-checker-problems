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
        
        auto path = SbtOperators::encode({ a, b });
        long long len = 0;
        for(auto cn : path) len += cn.second;
        if(len < K_MIN_ANCESTOR){ i--; continue; }
        long long k = gen.uniform<long long>(K_MIN_ANCESTOR, std::min<long long>(len, K_MAX_ANCESTOR));
        printf("ANCESTOR %lld %lld %lld\n", k, a, b);
    }

    return 0;
}
