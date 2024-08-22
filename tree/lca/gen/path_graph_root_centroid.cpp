#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int q = Q_MAX;
    
    int m = n / 2;
    /** 
     * Make path graph like the figure below
     * 
     * (0) -- (  1  ) -- ... -- (m - 1) 
     *  |
     * (m) -- (m + 1) -- ... -- (N - 1) 
     * 
     */
    
    printf("%d %d\n", n, q);
    for (int i = 1; i < n; i++) {
        printf("%d", i == m ? 0 : i - 1);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int u = gen.uniform<int>(0, m - 1);
        int v = gen.uniform<int>(m, n - 1);
        printf("%d %d\n", u, v);
    }
    return 0;
}
