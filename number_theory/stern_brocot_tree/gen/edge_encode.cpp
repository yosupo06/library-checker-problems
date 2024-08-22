
#include "../params.h"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    auto [A, B] = EdgeCoprime(T_MAX, TARGET_FRAC_MAX);

    long long z = A.size();
    
    // output T
    printf("%lld\n", z);

    for(long long i=0; i<z; i++){
        printf("ENCODE_PATH %lld %lld\n", A[i], B[i]);
    }

    return 0;
}
