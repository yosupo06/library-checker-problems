#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100;
    
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        int x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        int y = 0;
        printf("%d %d\n", x, y);
    }
    return 0;
}
