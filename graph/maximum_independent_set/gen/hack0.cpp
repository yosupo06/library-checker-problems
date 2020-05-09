#include <iostream>
#include "random.h"
#include "../params.h"

int main(int, char**) {

    int n = N_MAX;
    int l = 10;
    int m = l * (n - l);

    printf("%d %d\n", n, m);
    for (int i = 0; i < l; ++i) {
        for (int j = l; j < n; ++j) {
            printf("%d %d\n", i, j);
        }
    }
    return 0;
}
