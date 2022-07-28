#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = 500;
    int k = gen.uniform(2, 20);
    int l = n / k;
    printf("%d %d\n", n, (k - 1) * l * l);
    for (int i = 1; i < k; i++) {
        for (int u = 0; u < l; ++u) {
            for (int v = 0; v < l; ++v) {
                printf("%d %d %d\n", (i - 1) * l + u, i * l + v, gen.uniform(1, 1000000));
            }
        }
    }
    return 0;
}
