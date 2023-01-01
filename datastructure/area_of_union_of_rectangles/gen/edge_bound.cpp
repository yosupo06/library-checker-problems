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
        auto [L,R]=gen.uniform_pair<int>(0,COORD_MAX);
        int width=gen.uniform<int>(1,10000);
        int D=gen.uniform<int>(0,COORD_MAX-width),U=D+width;
        if(gen.uniform_bool())swap(L,D),swap(R,U);
        printf("%d %d %d %d\n",L,D,R,U);
    }
    
    return 0;
}
