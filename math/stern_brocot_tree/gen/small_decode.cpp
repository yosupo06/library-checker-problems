
#include "../params.h"
#include "../lib/gcd.hpp"
#include "../lib/lib.hpp"
#include "../lib/gen_lib.hpp"
#include <vector>
#include <cstdio>

int main(int, char*[]) {
    long long max_ab = LargestIf([](long long x){ return x*x <= T_MAX; });

    auto [A, B] = SmallCoprime(max_ab);

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
