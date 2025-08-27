#include "../params.h"
#include "random.h"
#include <cstdio>
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_AND_Q_MAX;
    int Q = N_AND_Q_MAX;
    printf("%d %d\n", N, Q);

    for(int i=0; i<N; i++){
        int a = gen.uniform<int>(1, MOD - 1);
        int b = gen.uniform<int>(0, MOD - 1);
        printf("%d %d\n", a, b);
    }

    for(int i=0; i<N-1; i++){
        printf("%d %d\n", i, i+1);
    }

    for(int i=0; i<Q; i++){
        int x = gen.uniform<int>(0, MOD - 1);
        if(i%2 == 0){
            printf("2 %d %d %d\n", 0, N-1, x);
        } else {
            printf("2 %d %d %d\n", N-1, 0, x);
        }
    }

    return 0;
}
