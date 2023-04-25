#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    
    int Q = MAX_Q;
    printf("%d\n", Q);
    for(int i = 0; i < Q; i++) {
        printf("%lld\n", gen.uniform<ll>(1, MAX_N));
    }
}
