#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(1, MAX_N);
    int Q = gen.uniform<int>(1, MAX_Q);
    printf("%d %d\n", N, Q);
    
    for(int i=0; i<N; i++) {
        printf("%d%c", gen.uniform<int>(0, MAX_A), " \n"[i + 1 == N]);
    }

    for(int i=0; i<Q; i++) {
        int l = gen.uniform<int>(0, N-1);
        int r = gen.uniform<int>(l+1, N);
        printf("%d %d\n", l, r);
    }
    
    return 0;
}
