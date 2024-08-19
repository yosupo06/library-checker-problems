
#include "../params.h"
#include "../lib/gcd.hpp"
#include "../lib/lib.hpp"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    auto [A, B] = EdgeCoprime(T_MAX, TARGET_FRAC_MAX);

    long long z = A.size();
    
    // output T
    printf("%lld\n", z);

    for(long long i=0; i<z; i++){
        auto path = SbtOperators::encode({ A[i], B[i] });
        printf("DECODE_PATH ");
        output_path(path);
        printf("\n");
    }

    return 0;
}
