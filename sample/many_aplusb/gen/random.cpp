#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(0, T_MAX);    
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        auto a = gen.uniform(0LL, A_AND_B_MAX);
        auto b = gen.uniform(0LL, A_AND_B_MAX);
        printf("%lld %lld\n", a, b);
    }
    return 0;
}
