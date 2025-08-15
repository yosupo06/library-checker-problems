#include <cstdio>
#include "../params.h"

using namespace std;

int main() {
    int n = (1<<18);
    int q = 500000;

    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%d", 0);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int t = (i%2);
        printf("%d ", t);
        if (t == 0) {
            int l = 0, r = n, x = 1;
            printf("%d %d %d\n", l, r, x);
        } else {
            int l = 1, r = n-1;
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
