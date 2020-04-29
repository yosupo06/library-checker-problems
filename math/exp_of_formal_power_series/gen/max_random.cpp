#include <cstdio>
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    printf("%d\n", n);

    printf("0");
    for (int i = 1; i < n; i++) {
        printf(" %d", gen.uniform(0, 998244352));
    }
    printf("\n");
    return 0;
}
