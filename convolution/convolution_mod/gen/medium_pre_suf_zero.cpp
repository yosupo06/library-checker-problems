// almost copy of midium.cpp

#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1000; // fixed
    int m = n; // fixed
    vector<int> a(n), b(m);

    for (int i = 0; i < n; i++) {
        a[i] = gen.uniform(0ll, MOD - 1);
    }
    for (int i = 0; i < m; i++) {
        b[i] = gen.uniform(0ll, MOD - 1);
    }

    // writing zeros
    if(seed%5 == 0){ a[0] = b[0] = 0; }
    if(seed%5 == 1){ a[n-1] = b[m-1] = 0; }
    if(seed%5 == 2){
        for(int i=1; i<n; i++) a[i] = 0;
        for(int i=1; i<m; i++) b[i] = 0;
    }
    if(seed%5 == 3){
        for(int i=0; i<n-1; i++) a[i] = 0;
        for(int i=0; i<m-1; i++) b[i] = 0;
    }
    if(seed%5 == 4){
        a[0] = b[0] = 0;
        a[n-1] = b[m-1] = 0;
    }
    //

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d", b[i]);
        if (i != m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
