#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500);
    int m = gen.uniform(1, 500);

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

    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
            if (j + 1 != m) cout << " ";
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        cout << b[i];
        if (i + 1 != n) cout << " ";
    }
    printf("\n");

    return 0;
}
