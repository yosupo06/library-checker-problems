#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);
    int m = gen.uniform(1, 500'000);
    printf("p cnf %d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int a = 0, b = 0;
        while (!a) a = gen.uniform(-n, n);
        while (!b) b = gen.uniform(-n, n);
        printf("%d %d 0\n", a, b);
    }
    return 0;
}
