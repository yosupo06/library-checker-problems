#include <iostream>
#include <vector>
#include <algorithm>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int density_idx = seed / 2 + 2;
    int n = min<int>(N_MAX, M_MAX * 2 / density_idx);

    int m = M_MAX;
    int k = K_MAX;
    int s=gen.uniform<int>(0,n-1);
    int t=gen.uniform<int>(0,n-1);
    printf("%d %d %d %d %d\n",n,m,s,t,k);
    for (int i = 0; i < m; i++) {
        int u,v,c;
        u=gen.uniform(0,n-1);
        v=gen.uniform(0,n-1);
        c=gen.uniform(C_MIN,C_MAX);
        printf("%d %d %d\n",u,v,c);
    }
    return 0;
}