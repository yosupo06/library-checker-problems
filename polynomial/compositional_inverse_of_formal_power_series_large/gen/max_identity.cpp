#include "../params.h"
#include "random.h"

#include <stdio.h>

int main() {
    int n = N_MAX;
    printf("%d\n", n);
    printf("0 1");
    for (int i = 2; i < n; i++) {
        printf(" 0");
    }
    puts("");
    return 0;
}
