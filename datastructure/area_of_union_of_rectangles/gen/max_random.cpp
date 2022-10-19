#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;
    printf("%d\n", N);
    
    for (int i = 0; i < N; i++) {
        int L=gen.uniform<int>(0,COORD_MAX);
        if(L==COORD_MAX)L--;
        int R=gen.uniform<int>(L+1,COORD_MAX);
        int D=gen.uniform<int>(0,COORD_MAX);
        if(D==COORD_MAX)D--;
        int U=gen.uniform<int>(D+1,COORD_MAX);
        printf("%d %d %d %d\n",L,D,R,U);
    }
    
    return 0;
}
