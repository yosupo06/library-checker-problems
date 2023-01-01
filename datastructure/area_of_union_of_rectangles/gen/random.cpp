#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(1,N_MAX);
    printf("%d\n", N);
    
    for (int i = 0; i < N; i++) {
        auto [L,R]=gen.uniform_pair<int>(0,COORD_MAX);
        auto [D,U]=gen.uniform_pair<int>(0,COORD_MAX);
        printf("%d %d %d %d\n",L,D,R,U);
    }
    
    return 0;
}
