#include <iostream>
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;

    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = gen.uniform(0, 998244353);
    }
    int m = gen.uniform(1, n);
    for (int i = 0; i < m; i++) {
        f[i] = 0;
    }

    cout << n << endl;

    for (int i = 0; i < n; i++) {
        cout << f[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
