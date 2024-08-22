#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

long long f(long long x){ return x*x + x; }

int main(int, char** argv){
    long long upper = 1;
    while(f(upper) <= N_MAX) upper++;
    upper--;

    long long case_id = atoll(argv[1]);
    Random gen(case_id);
    
    if(case_id == 0){
        long long n = f(upper);
        printf("%lld\n", n);
    }
    else{
        long long n = f(gen.uniform<long long>(10, upper));
        printf("%lld\n", n);
    }
    return 0;
}
