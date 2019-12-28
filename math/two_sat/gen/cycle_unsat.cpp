#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000 - 2;
    int m = 500'000;

    printf("p cnf %d %d\n", n, m);

    // all same
    for (int i = 1; i < n; i++) {
        printf("%d %d 0\n", i, - (i + 1));
    }
    printf("%d -1 0\n", n);

    // some pair, both true(= all true)
    int a = gen.uniform(1, n);
    int b = gen.uniform(1, n);
    printf("%d %d 0\n", a, b);
    // some pair, both false(= all false)
    a = gen.uniform(-n, -1);
    b = gen.uniform(-n, -1);
    printf("%d %d 0\n", a, b);
    return 0;
}
