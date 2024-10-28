#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = gen.uniform<int>(0, MOD - 1);
        }
    }

    if(gen.uniform01()) { // create a linear dependency in rows
        int i = gen.uniform(0, n - 1);
        int j = gen.uniform(0, n - 1);
        int k = gen.uniform(0, n - 1);
        auto A = gen.uniform<int64_t>(0, MOD - 1);
        auto B = gen.uniform<int64_t>(0, MOD - 1);
        for(int l = 0; l < n; l++) {
            a[i][l] = (A * a[j][l] + B * a[k][l]) % MOD;
        }
    }
    if(gen.uniform01()) { // create a linear dependency in columns
        int i = gen.uniform(0, n - 1);
        int j = gen.uniform(0, n - 1);
        int k = gen.uniform(0, n - 1);
        auto A = gen.uniform<int64_t>(0, MOD - 1);
        auto B = gen.uniform<int64_t>(0, MOD - 1);
        for(int l = 0; l < n; l++) {
            a[l][i] = (A * a[l][j] + B * a[l][k]) % MOD;
        }
    }

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", a[i][j], " \n"[j + 1 == n]);
        }
    }
    return 0;
}
