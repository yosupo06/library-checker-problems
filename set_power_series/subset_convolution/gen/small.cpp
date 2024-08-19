#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = seed % 3;
    printf("%d\n", n);
    for (int i = 0; i < (1 << n); i++) {
        int x = gen.uniform<int>(0, MOD - 1);
        printf("%d", x);
        if (i != (1 << n) - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < (1 << n); i++) {
        int x = gen.uniform<int>(0, MOD - 1);
        printf("%d", x);
        if (i != (1 << n) - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
