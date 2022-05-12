#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    long long MAXI = 1000000000000000000ll;
    int Q = 1000000;
    long long mask = (1ll << 50) - 1;

    printf("%d\n", Q);

    int query0_col = 400000;
    int query0_one = 400000;
    int query1 = 200000;

    printf("%d %lld %d\n", 0, mask + 2, 1);

    long long int k = 6;
    for(int i = 1; i < query0_col; i++){
        long long v = gen.uniform<long long>(0, MAXI);
        printf("%d %lld %lld\n", 0, k, v);
        k = k * 5 + 1;
        k &= mask;
    }

    for(int i = 0; i < query0_one; i++){
        long long v = gen.uniform<long long>(0, MAXI);
        printf("%d %lld %lld\n", 0, 1ll, v);
    }

    
    for(int i = 0; i < query1; i++){
        printf("%d %d\n", 1, i);
    }
    return 0;
}
