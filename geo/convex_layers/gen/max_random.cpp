#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        //possible but very unlikely that two points coincide 
        auto a = gen.uniform(0LL, X_AND_Y_MAX);
        auto b = gen.uniform(0LL, X_AND_Y_MAX);
        printf("%lld %lld\n", a, b);
    }
    return 0;
}
