#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 1 << 17);
    vector<int> x = gen.choice(n, 0, 998244353);
    vector<int> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = gen.uniform(0, 998244353);
    }

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", y[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
