
#include <cstdio>
#include "../params.h"

int main(){
    int N = N_MAX;
    printf("%d\n", N);
    for(int i=1; i<N; i++){
        if(i != 1) printf(" ");
        printf("%d", i - 1);
    }
    printf("\n");
    return 0;
}
