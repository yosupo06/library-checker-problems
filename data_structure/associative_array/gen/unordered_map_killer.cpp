#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"
using namespace std;

/*
このコードでMAGICが計算可能

#include <iostream>
#include <unordered_map>
using ll = long long;
using namespace std;
int main() {
    int m = 1000000;
    unordered_map<int,int> f;
    int old = -1;
    for (int i = 0; i < m; i++) {
        int now = int(f.bucket_count());
        if (old != now) {
            cout << old << " -> " << now << endl;
            old = now;
        }
        f[i] = i;
    }
    return 0;
}
*/

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    // magic for ideone, judge, clang++(OS X)
    int MAGIC = vector<int>({256279, 218971, 205759})[seed % 3];

    int Q = Q_MAX;
    printf("%d\n", Q);

    vector<long long> keys;
    for (long long i = 0; i <= K_AND_V_MAX; i += MAGIC) {
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
