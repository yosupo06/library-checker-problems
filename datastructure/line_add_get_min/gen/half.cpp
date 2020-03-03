#include "random.h"
#include "../params.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = 2 * i;
        ll b = -i;;
        printf("%d %lld\n", a, b);
    }
    for (int i = 0; i < q; i++) {
        int x = gen.uniform(0, 1);
        printf("1 %d\n", x);
    }
    return 0;
}
