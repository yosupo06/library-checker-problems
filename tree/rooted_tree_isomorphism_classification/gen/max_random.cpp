
#include <cstdio>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;

    printf("%d\n", N);
    for(int i=1; i<N; i++){
        int p = gen.uniform(0, i-1);
        if(i != 1) printf(" ");
        printf("%d", p);
    }
    printf("\n");
    return 0;
}
