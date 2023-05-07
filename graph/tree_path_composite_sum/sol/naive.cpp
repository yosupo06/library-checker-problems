
#include <cstdio>
#include <vector>
#include <array>

int main(){

    constexpr long long MOD = 998244353;

    auto nextInt = []() -> int { int a; scanf("%d", &a); return a; };

    int N = nextInt();
    if(N > 500) return 0;

    std::vector<int> A(N), B(N-1), C(N-1);
    for(int i=0; i<N; i++) A[i] = nextInt();

    std::vector<int> xorEdge(N-1);
    std::vector<std::vector<int>> adj(N);
    for(int i=0; i<N-1; i++){
        int u = nextInt();
        int v = nextInt();
        B[i] = nextInt();
        C[i] = nextInt();
        xorEdge[i] = u ^ v;
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    for(int s=0; s<N; s++){
        std::vector<int> bfs = {s};
        std::vector<int> par(N, -1);
        for(int i=0; i<N; i++){
            int v = bfs[i];
            for(int e : adj[v]) if(par[v] != e){
                int w = xorEdge[e] ^ v;
                bfs.push_back(w);
                par[w] = e;
            }
        }

        long long ans = 0;
        
        for(int t=0; t<N; t++){
            int p = t;
            long long x = A[t];
            while(p != s){
                int e = par[p];
                x = (B[e] * x + C[e]) % MOD;
                p = xorEdge[e] ^ p;
            }
            ans += x;
        }

        if(s) printf(" ");
        printf("%lld", ans % MOD);
    }

    printf("\n");
    return 0;
}
