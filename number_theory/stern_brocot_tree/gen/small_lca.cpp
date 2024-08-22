
#include "../params.h"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    long long max_ab = LargestIf([](long long x){ return x*x*x*x <= T_MAX; });

    auto [A, B] = SmallCoprime(max_ab);

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
