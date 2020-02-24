#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char**) {
    printf("121\n");
    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            printf("%d %d\n", i, j);
        }
    }
    return 0;
}
