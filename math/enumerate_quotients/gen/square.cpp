#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main(int, char** argv){
    long long upper = 1;
    while(upper * upper <= N_MAX) upper++;
    upper--;

    Random gen(atoll(argv[1]));
    long long n = gen.uniform(N_MIN, upper);
    n = n * n;
    printf("%lld\n", n);
    return 0;
}
