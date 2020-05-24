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

    vector<long long> keys;

    for (long long i = 0; i <= K_AND_V_MAX; i += 1LL << 39) {
        keys.push_back(i);
        if (int(keys.size()) == 1'000'000) break;
    }

    int K = int(keys.size());
    
    for (int i = 0; i < Q; i++) {
        bool type = gen.uniform_bool();
        if (!type) {
            long long key = keys[i % K];
            long long val = gen.uniform(0LL, K_AND_V_MAX);
            printf("0 %lld %lld\n", key, val);
        } else {
            long long key = keys[i % K];
            printf("1 %lld\n", key);
        }
    }
    
    return 0;
}
