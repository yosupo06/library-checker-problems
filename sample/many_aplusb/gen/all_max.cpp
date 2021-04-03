#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char**) {
    int t = T_MAX;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        auto a = A_AND_B_MAX;
        auto b = A_AND_B_MAX;
        printf("%lld %lld\n", a, b);
    }
    return 0;
}
