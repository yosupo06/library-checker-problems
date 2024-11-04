#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>

// simple graph
// for each edge
// O( n + m sqrt(m) ) time
std::vector<long long> CountC4Simple(
    int n,
    std::vector<int> U,
    std::vector<int> V,
    std::vector<long long> W
){
    int m = int(W.size());
    
    // less incident edges, smaller index
    std::vector<int> deg(n);
    for(int e=0; e<m; e++){ deg[U[e]]++; deg[V[e]]++; }
    std::vector<int> I(n); for(int i=0; i<n; i++) I[i] = i;
    std::stable_sort(I.begin(), I.end(), [&](int l, int r){ return deg[l] < deg[r]; });
    {
        std::vector<int> O(n);
        for(int i=0; i<n; i++) O[I[i]] = i;
        for(int& u : U) u = O[u];
        for(int& u : V) u = O[u];
    }

    for(int e=0; e<m; e++) if(U[e] < V[e]) std::swap(U[e], V[e]);
    
    // adjacency list

    std::vector<int> estart(n);
    for(int i=0; i<n-1; i++) estart[i+1] = estart[i] + deg[I[i]];
    std::vector<int> eend = estart;
    std::vector<int> eid(m*2);
    std::vector<int> eto(m*2);

    for(int e=0; e<m; e++){
        int v = U[e];
        int w = V[e];
        eid[eend[v]] = e;
        eto[eend[v]] = w;
        eend[v]++;
    }
    std::vector<int> eendx = eend;
    for(int v=0; v<n; v++){
        for(int i=estart[v]; i<eendx[v]; i++){
            int e = eid[i];
            int w = eto[i];
            eid[eend[w]] = e;
            eto[eend[w]] = v;
            eend[w]++;
        }
    }
    
    std::vector<long long> c(n); // c[x] : number of paths(v --> w --> x)
    std::vector<long long> ans(m);
    for(int v=n-1; v>=0; v--){
        for(int i=estart[v]; i<eend[v]; i++){
            int evw = eid[i];
            int w = eto[i];
            eend[w] -= 1; // remove w -> v
            for(int j=estart[w]; j<eend[w]; j++){
                int ewx = eid[j];
                int x = eto[j];
                c[x] += W[evw] * W[ewx];
            }
        }
        for(int i=estart[v]; i<eend[v]; i++){
            int evw = eid[i];
            int w = eto[i];
            for(int j=estart[w]; j<eend[w]; j++){
                int ewx = eid[j];
                int x = eto[j];
                long long val = c[x] - W[evw] * W[ewx];
                ans[evw] += val * W[ewx];
                ans[ewx] += val * W[evw];
            }
        }
        for(int i=estart[v]; i<eend[v]; i++){
            int w = eto[i];
            for(int j=estart[w]; j<eend[w]; j++) c[eto[j]] = 0;
        }
    }
    return ans;
}

// for each edge
// O( n + m sqrt(m) ) time
std::vector<long long> CountC4(
    int n,
    std::vector<int> U,
    std::vector<int> V,
    std::vector<long long> W
){
    int m = int(W.size());
    for(int i=0; i<m; i++) if(U[i] > V[i]) std::swap(U[i], V[i]);
    std::vector<int> I(m);
    for(int i=0; i<m; i++) I[i] = i;
    std::stable_sort(I.begin(), I.end(), [&](int l, int r){ return V[l] < V[r]; });
    std::stable_sort(I.begin(), I.end(), [&](int l, int r){ return U[l] < U[r]; });

    std::vector<int> Q(m);
    std::vector<int> U2;
    std::vector<int> V2;
    std::vector<long long> W2;
    for(int i=0; i<m; i++){
        int e = I[i];
        if(i == 0 || U2.back() != U[e] || V2.back() != V[e]){
            U2.push_back(U[e]);
            V2.push_back(V[e]);
            W2.push_back(0);
        }
        W2.back() += W[e];
        Q[e] = int(U2.size()) - 1;
    }

    auto simple_res = CountC4Simple(n, std::move(U2), std::move(V2), std::move(W2));
    std::vector<long long> ans(m);
    for(int e=0; e<m; e++) ans[e] = simple_res[Q[e]];
    return ans;
}

using namespace std;

int main(){
    int N, M; scanf("%d%d", &N, &M);
    std::vector<int> U(M), V(M);
    for(int i=0; i<M; i++) scanf("%d%d", &U[i], &V[i]);
    auto ans = CountC4(N, U, V, std::vector<long long>(M, 1));
    for(int i=0; i<M; i++){
        if(i) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
