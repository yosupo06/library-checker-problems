#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = (1 << 17);
    vector<int> x = gen.choice(n, 0, 998244353);
    vector<int> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = gen.uniform(0, 998244353);
    }

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << x[i];
        if (i != n - 1) cout << " ";
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        cout << y[i];
        if (i != n - 1) cout << " ";
    }
    printf("\n");
    return 0;
}
