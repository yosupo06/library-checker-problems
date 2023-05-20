#include "../lib/any-direction-tree-dp.hpp"
#include "../lib/static-modint.hpp"

#include <cstdio>
#include <vector>
#include <array>

int main(){
    using Modint = nachia::StaticModint<998244353>;

    auto nextInt = []() -> int { int a; scanf("%d", &a); return a; };

    int N = nextInt();

    std::vector<Modint> A(N), B(N-1), C(N-1);
    for(int i=0; i<N; i++) A[i] = Modint::raw(nextInt());

    nachia::Graph tree(N, true);
    for(int i=0; i<N-1; i++){
        int u = nextInt();
        int v = nextInt();
        B[i] = Modint::raw(nextInt());
        C[i] = Modint::raw(nextInt());
        tree.addEdge(u, v);
    }

    using SemiCluster = std::array<Modint, 2>;

    // f(T,r) for some pairs (T, r) : tree T and its root r
    //
    //     f(T,r)[0] = sum_{v \in T , v \neq r} P(r, v)
    //     f(T,r)[1] = sum_{v \in T , v \neq r} 1
    //
    // if T has only 1 edge e=(r,c) incident to r,
    //
    //     f(T,r)[0] = sum_{v} P(r, v)
    //               = sum_{v} f_e( P(c, v) )
    //               = sum_{v} ( C_e + B_e P(c, v) )
    //               = C_e sum_{v} 1 + B_e sum_{v} P(c, v)
    //               = C_e ( f(T',c)[1] + 1 ) + B_e ( f(T',c)[0] + A[c] )

    auto treeDp = nachia::AnyDirectionTreeDP(
        tree,
        std::vector<SemiCluster>(N, {0,0}),
        [&](SemiCluster a, SemiCluster b) -> SemiCluster {
            return { a[0]+b[0], a[1]+b[1] };
        },
        [&](SemiCluster a, int e, int r) -> SemiCluster {
            int c = tree[e].from ^ tree[e].to ^ r;
            return { C[e] * (a[1] + 1) + B[e] * (a[0] + A[c]), a[1] + 1 };
        }
    );

    for(int i=0; i<N; i++){
        if(i) printf(" ");
        Modint ans = treeDp.getAtVtx(i)[0] + A[i];
        printf("%d", (int)ans.val());
    }
    printf("\n");
    return 0;
}
