#include "random.h"
#include <cstdio>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500'000);

    printf("%d", n);

    printf("1");
    for (int i = 1; i < n; i++) {
        printf(" %d", gen.uniform(0, 998244353));
    }
    printf("\n");
    return 0;
}
