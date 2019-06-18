#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2800, 3000);
    vector<int> a = gen.perm<int>(n);
    vector<int> b = gen.perm<int>(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = gen.uniform(1, 998244353 - 1);
    }

    cout << n << " " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << endl;
    }
    return 0;
}
