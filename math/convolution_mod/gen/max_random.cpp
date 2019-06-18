#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1 << 19;
    int m = 1 << 19;
    vector<int> a(n), b(m);

    for (int i = 0; i < n; i++) {
        a[i] = gen.uniform(0, 998244353);
    }
    for (int i = 0; i < m; i++) {
        b[i] = gen.uniform(0, 998244353);
    }

    cout << n << " " << m << endl;

    for (int i = 0; i < n; i++) {
        cout << a[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << b[i];
        if (i != m - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
