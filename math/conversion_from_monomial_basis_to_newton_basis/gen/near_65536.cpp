#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[]) {
    int case_number = atoll(argv[1]);
    Random rng(case_number ^ 0x924eea7b1998de01);
    
    int n = 65536 - 2 + case_number;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng.uniform(0ll, MOD - 1);
    }
    vector<int> p(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        p[i] = rng.uniform(0ll, MOD - 1);
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d", a[i]);
        if (i != n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i < n - 1; ++i) {
        printf("%d", p[i]);
        if (i != n - 2) {
            printf(" ");
        }
    }
    printf("\n");
}