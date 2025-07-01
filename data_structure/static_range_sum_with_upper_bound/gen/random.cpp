#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(1, MAX_N_Q);
    int Q = gen.uniform<int>(1, MAX_N_Q);
    printf("%d %d\n", N, Q);
    
    for(int i=0; i<N; i++) {
        printf("%d%c", gen.uniform<int>(0, MAX_A_X), " \n"[i + 1 == N]);
    }

    for(int i=0; i<Q; i++) {
        int t, l, r, x;
        t = gen.uniform<int>(0, MAX_A_X)%2;
        std::tie(l, r) = gen.uniform_pair<int>(0, N);
        x = gen.uniform<int>(0, MAX_A_X);
        printf("%d %d %d %d\n", t, l, r, x);
    }
    
    return 0;
}
