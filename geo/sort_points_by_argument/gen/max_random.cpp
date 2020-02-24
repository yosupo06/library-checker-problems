#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        int x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        int y = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        printf("%d %d\n", x, y);
    }
    return 0;
}
