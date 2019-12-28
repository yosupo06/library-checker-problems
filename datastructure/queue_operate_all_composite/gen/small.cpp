#include "random.h"
#include <iostream>

using namespace std;

const int MOD = 998244353;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = gen.uniform(1, 5);
    printf("%d\n", 2 * q);

    int length = 0;
    for (int i = 0; i < q; i++) {
        const int table[4] = { 0, 0, 1 };
        int t = table[gen.uniform(0, 3 - 1)];
        if (length == 0 and t == 1) {
            t = 0;
        }
        printf("%d", t);
        if (t == 0) {
            int a = gen.uniform(1, 10);
            int b = gen.uniform(0, 10);
            printf(" %d %d", a, b);
            length++;
        } else if (t == 1) {
            length--;
        } else {
            int x = gen.uniform(0, MOD - 1);
            printf(" %d", x);
        }
        printf("\n");
        int x = gen.uniform(0, 10);
        printf("2 %d\n", x);
    }
    return 0;
}
