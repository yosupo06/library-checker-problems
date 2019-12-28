#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);
    int m = gen.uniform(1, 500'000);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        printf("%d %d\n", a, b);
    }
    return 0;
}
