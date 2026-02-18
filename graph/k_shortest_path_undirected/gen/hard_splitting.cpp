#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int clique_n = 7;
    int clique_m = clique_n * (clique_n - 1) / 2;
    int len = 1;
    while(clique_n + (len+1) <= N_MAX && clique_m + (len+1) * 2 - 1 <= M_MAX) len += 1;

    int n = clique_n + len;
    int m = clique_m + len * 2 - 1;
    int k = K_MAX;
    int s = 0;
    int t = n - 1;

    vector<int> U, V, W;
    auto add_edge = [&](int u, int v, int w){
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);
    };

    for(int i=0; i<clique_n; i++) for(int j=i+1; j<clique_n; j++){
        int c = gen.uniform(C_MIN, C_MIN + 31);
        add_edge(i, j, c);
    }

    for(int i=clique_n-1; i+1<n; i++){
        int c = gen.uniform(C_MIN, C_MIN + 31);
        add_edge(i, i+1, c);
    }

    for(int i=clique_n-1; i+2<n; i++){
        int c = gen.uniform(C_MAX - 31, C_MAX);
        add_edge(i, i+2, c);
    }

    auto pv = gen.perm<int>(n);
    auto pe = gen.perm<int>(m);
    for(int i=0; i<n; i++) pv[i] = i;
    for(int i=0; i<m; i++) pe[i] = i;
    printf("%d %d %d %d %d\n",n,m,pv[s],pv[t],k);
    for(int e : pe){
        printf("%d %d %d\n", pv[U[e]], pv[V[e]], W[e]);
    }
    return 0;
}