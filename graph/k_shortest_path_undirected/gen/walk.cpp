#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int th = 5;
    int len = 1;
    while(len + 2 < N_MAX && (len + 1) * th < M_MAX) len += 1;

    int n = 1 + len;
    int m = len * th;
    int k = K_MAX;
    int s = 0;
    int t = n - 1;

    vector<int> U, V, W;
    auto add_edge = [&](int u, int v, int w){
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);
    };

    for(int i=0; i<len; i++) for(int t=0; t<th; t++){
        int c = gen.uniform(C_MIN, C_MAX);
        add_edge(i, i+1, c);
    }

    auto pv = gen.perm<int>(n);
    auto pe = gen.perm<int>(m);
    printf("%d %d %d %d %d\n",n,m,pv[s],pv[t],k);
    for(int e : pe){
        printf("%d %d %d\n", pv[U[e]], pv[V[e]], W[e]);
    }
    return 0;
}