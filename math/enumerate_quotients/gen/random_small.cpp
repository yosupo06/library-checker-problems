#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main(int, char** argv){
    Random gen(atoll(argv[1]));
    long long n = gen.uniform(N_MIN, 1000'000ll);
    printf("%lld\n", n);
    return 0;
}
