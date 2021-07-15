#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500;
    int m = n - 1;

    printf("%d %d\n", n, m);
    for (int i = 1; i < n; i++) {
        int w = gen.uniform(1, 1000000);
        printf("%d %d %d\n", i >> 1, i, w);
    }
    return 0;
}
