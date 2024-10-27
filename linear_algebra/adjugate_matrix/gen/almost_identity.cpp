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
        a[i][i] = 1;
    }
    int t = gen.uniform(0, n - 1);
    a[t][t] = 0;
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", a[i][j], " \n"[j + 1 == n]);
        }
    }
    return 0;
}
