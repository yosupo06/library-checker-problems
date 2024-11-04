#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
using namespace std;

int main(){
    int N, M; scanf("%d%d", &N, &M);
    std::vector<int> U(M), V(M);
    for(int i=0; i<M; i++) scanf("%d%d", &U[i], &V[i]);
    for(int i=0; i<M; i++) if(U[i] > V[i]) std::swap(U[i], V[i]);
    std::vector<long long> ans(M);
    int D[8] = {};
    for(int i=0; i<M; i++){
        for(int j=i+1; j<M; j++){
            if(U[i] == U[j] && V[i] == V[j]) continue;
            for(int k=j+1; k<M; k++){
                if(U[i] == U[k] && V[i] == V[k]) continue;
                if(U[j] == U[k] && V[j] == V[k]) continue;
                for(int f=k+1; f<M; f++){
                    D[0] = U[i];
                    D[1] = V[i];
                    D[2] = U[j];
                    D[3] = V[j];
                    D[4] = U[k];
                    D[5] = V[k];
                    D[6] = U[f];
                    D[7] = V[f];
                    std::sort(D, D+8);
                    if(D[0] == D[1] && D[1] != D[2] && D[2] == D[3] && D[3] != D[4] && D[4] == D[5] && D[5] != D[6] && D[6] == D[7]){
                        ans[i] += 1;
                        ans[j] += 1;
                        ans[k] += 1;
                        ans[f] += 1;
                    }
                }
            }
        }
    }
    for(int i=0; i<M; i++){
        if(i) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
