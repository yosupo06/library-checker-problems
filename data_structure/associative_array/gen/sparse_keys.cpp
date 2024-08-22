#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int Q = gen.uniform<int>(1, Q_MAX);
    printf("%d\n", Q);
    int K = gen.uniform(1, 100);
    vector<long long> keys(K);
    for (auto& x: keys) {
        x = gen.uniform(0LL, K_AND_V_MAX);
    }
    
    for (int i = 0; i < Q; i++) {
        bool type = gen.uniform_bool();
        if (!type) {
            long long key = keys[gen.uniform(0, K - 1)];
            long long val = gen.uniform(0LL, K_AND_V_MAX);
            printf("0 %lld %lld\n", key, val);
        } else {
            long long key = keys[gen.uniform(0, K - 1)];
            printf("1 %lld\n", key);
        }
    }
    
    
    return 0;
}
