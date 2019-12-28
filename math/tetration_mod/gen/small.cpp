#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main() {

    int l = 10;
    int t = l * l * l;
    printf("%d\n", t);
    for (int a = 0; a < l; a++) {
        for (int b = 0; b < l; b++) {
            for (int m = 1; m <= l; m++) {
                printf("%d %d %d\n", a, b, m);
            }
        }
    }
    return 0;
}
