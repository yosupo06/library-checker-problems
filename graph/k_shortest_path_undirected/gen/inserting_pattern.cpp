#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

bool acceptable(int base_length, int num_insert){
    int n = 1 + base_length + num_insert;
    int m = base_length + num_insert * 2;
    return n <= N_MAX && m <= M_MAX;
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int base_length = 1;
    int num_insert = 1;
    while(num_insert < K_MAX + 10 && acceptable(base_length + 1, num_insert + 1)){
        base_length += 1;
        num_insert += 1;
    }
    while(acceptable(base_length + 1, num_insert)){
        base_length += 1;
    }

    int n = 1 + base_length + num_insert;
    int m = base_length + num_insert * 2;
    int k = K_MAX;
    int s = 0;
    int t = base_length;

    vector<int> U, V, W;
    auto add_edge = [&](int u, int v, int w){
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);
    };

    for(int i=0; i<base_length; i++) add_edge(i, i+1, 1);

    // s/t                                t/s
    //   o-o-o-o-o-o-----------o-o-o-o-o-o
    //             |           |
    //             +---o-------+
    //                 |       |
    //                 +---o---+
    //                     |   |
    //                     +---+
    //
    if(seed == 0 || seed == 1){
        int p = base_length / 2, q = p + 1;
        for(int i=0; i<num_insert; i++){
            int v = base_length + 1 + i;
            int w = gen.uniform(C_MIN, C_MAX);
            add_edge(p, v, w);
            add_edge(v, q, w);
            (seed == 1 ? q : p) = v;
        }
    }

    // s                                   t
    // o-o-o-o---o-o-o-o---o-o-o-o---o-o-o-o
    //       |   |     |   |     |   |
    //       +-o-+     +-o-+     +-o-+
    //
    else if(seed == 2){
        auto perm = gen.perm<int>(base_length);
        for(int i=0; i<num_insert; i++){
            int p = perm[i];
            int q = perm[i] + 1;
            int v = base_length + 1 + i;
            int w = gen.uniform(C_MIN, C_MAX);
            add_edge(p, v, w);
            add_edge(v, q, w);
        }
    }

    auto pv = gen.perm<int>(n);
    auto pe = gen.perm<int>(m);
    printf("%d %d %d %d %d\n",n,m,pv[s],pv[t],k);
    for(int e : pe){
        printf("%d %d %d\n", pv[U[e]], pv[V[e]], W[e]);
    }
    return 0;
}