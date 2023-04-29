
#include "../params.h"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    auto [A, B] = EdgeCoprime(LargestIf([](long long x){ return x*x <= T_MAX; }), TARGET_FRAC_MAX);

    long long z = A.size();
    
    // output T
    printf("%lld\n", z*z);

    for(long long i=0; i<z; i++){
        for(long long j=0; j<z; j++){
            printf("LCA %lld %lld %lld %lld\n", A[i], B[i], A[j], B[j]);
        }
    }

    return 0;
}
