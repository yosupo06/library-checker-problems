#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int Q = Q_MAX;
    printf("%d\n", Q);
    vector<long long> keys = { 0LL };
    
    for (int i = 0; i < Q; i++) {
        bool type = gen.uniform(0, 99) == 0;
        if (!type) {
            long long key = gen.uniform(0LL, K_AND_V_MAX);
            long long val = gen.uniform(0LL, K_AND_V_MAX);
            printf("0 %lld %lld\n", key, val);
            keys.push_back(key);
        } else {
            long long key = keys[gen.uniform(0, (int) keys.size() - 1)];
            printf("1 %lld\n", key);
        }
    }
    
    return 0;
}
