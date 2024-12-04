#include <iostream>
#include <tuple>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    vector<int> query_freq;
    switch(seed){
        case 0 :
            query_freq = { 0 }; break;
        case 1 :
            query_freq = { 1 }; break;
        case 2 :
            query_freq = { 2 }; break;
        case 3 :
            query_freq = { 0,1 }; break;
        case 4 :
            query_freq = { 1,2 }; break;
        case 5 :
            query_freq = { 0,2 }; break;
        default :
            return 0;
    }

    int n = N_MAX;
    int q = Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform<int>(0, MOD - 1);
        printf("%d", a);
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    std::vector<int> data_enable;
    data_enable.push_back(-1);
    auto choose_data = [&]() -> int {
        int i = gen.uniform(0, (int)data_enable.size() - 1);
        return data_enable[i];
    };

    for (int i = 0; i < q; i++) {
        int t = query_freq[gen.uniform<int>(0, (int)query_freq.size()-1)];
        int k = choose_data();
        printf("%d %d ", t, k);
        if (t == 0) {
            int l, r;
            tie(l, r) = gen.uniform_pair(0, n);
            int b = gen.uniform<int>(1, MOD - 1);
            int c = gen.uniform<int>(0, MOD - 1);
            printf("%d %d %d %d\n", l, r, b, c);
            data_enable.push_back(i);
        } else if(t == 1) {
            int s = choose_data();
            auto [l,r] = gen.uniform_pair(0, n);
            printf("%d %d %d\n", s, l, r);
            data_enable.push_back(i);
        } else {
            auto [l,r] = gen.uniform_pair(0, n);
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
