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
        int a = gen.uniform(A_AND_X_MIN, A_AND_X_MAX);
        if(i) printf(" ");
        printf("%d", a);
    }
    printf("\n");

    for(int i=0; i<N-1; i++){
        printf("%d %d\n", i, i+1);
    }

    for(int i=0; i<Q; i++){
        if(i%2 == 0){
            printf("2 %d %d\n", 0, N-1);
        } else {
            printf("2 %d %d\n", N-1, 0);
        }
    }

    return 0;
}
