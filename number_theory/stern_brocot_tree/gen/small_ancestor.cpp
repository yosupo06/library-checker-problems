
#include "../params.h"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    long long max_ab = LargestIf([](long long x){ return x*x*(x+1) <= T_MAX; });

    auto [A, B] = SmallCoprime(max_ab);
    
    long long h = max_ab - K_MIN_ANCESTOR;

    long long z = A.size();

    // output T
    printf("%lld\n", z*h);

    for(long long i=0; i<z; i++){
        for(long long k=K_MIN_ANCESTOR; k<=h; k++){
            printf("ANCESTOR %lld %lld %lld\n", k, A[i], B[i]);
        }
    }

    return 0;
}
