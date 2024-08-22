#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_MAX);
    int q = gen.uniform<int>(1, Q_MAX);
    printf("%d %d\n", n, q);
    for (int i = 0; i < q; i++) {
        int ty = gen.uniform_bool();
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        printf("%d %d %d\n", ty, a, b);
    }
    return 0;
}