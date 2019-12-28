#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500);
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = gen.uniform(-1'000'000'000, 1'000'000'000);
        }
    }


    cout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
            if (j != n - 1) cout << " ";
        }
        printf("\n");
    }
    return 0;
}