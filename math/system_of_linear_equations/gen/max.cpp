#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500;
    int m = 500;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = gen.uniform(0, 998244353 - 1);
        }
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = gen.uniform(0, 998244353 - 1);
    }

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", a[i][j]);
            if (j + 1 != m) printf(" ");
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        printf("%d", b[i]);
        if (i + 1 != n) printf(" ");
    }
    printf("\n");

    return 0;
}
