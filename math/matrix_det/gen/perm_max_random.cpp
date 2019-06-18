#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(490, 500);
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> p = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        a[i][p[i]] = gen.uniform(0, 998244353 - 1);
    }

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
            if (j + 1 != n) cout << " ";
        }
        cout << endl;
    }
    return 0;
}
