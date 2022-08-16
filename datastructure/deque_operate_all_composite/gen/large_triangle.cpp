#include "random.h"
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int Q_MAX = 500'000;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int q = Q_MAX;
    printf("%d\n", q);

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        int t2_often = seed % 2;
        int t2 = t2_often ^ ((gen.uniform(0, 9) == 0) ? 1 : 0);
        if ((i / 50000) % 2 == 0) {
            if (t == 1) {
                t = 0;
            }
        } else {
            if (t == 0) {
                t = 1;
            }
        }
        if (length == 0 and t == 1) {
            t = 0;
        }
        t = t * 2 + t2; if(t == 5) t = 4;
        printf("%d", t);
        if (t == 0 || t == 1) {
            int a = gen.uniform(1, MOD - 1);
            int b = gen.uniform(0, MOD - 1);
            printf(" %d %d", a, b);
            length++;
        } else if (t == 2 || t == 3) {
            length--;
        } else {
            int x = gen.uniform(0, MOD - 1);
            printf(" %d", x);
        }
        printf("\n");
    }
    return 0;
}
